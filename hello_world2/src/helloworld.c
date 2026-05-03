/* color_cycle_baremetal.c
 * Uses: PS DisplayPort (psu_dp) + DPDMA + AVBuf
 * BSP libs needed: dppsu, dpdma, avbuf, dp (all present in your BSP)
 */

#include "xparameters.h"
#include "xdppsu.h"
#include "xdpdma.h"
#include "xavbuf.h"
#include "xil_cache.h"
#include "xil_printf.h"
#include "sleep.h"
#include <xil_types.h>
#include "xdppsu_hw.h"

#define XPAR_PSU_DP_DEVICE_ID 0xFD4A0000U
#define XPAR_PSU_DPDMA_DEVICE_ID 0xFD4C0000U

/* ---- frame buffer: 1920x1080 RGBA8888 ---- */
#define DISP_WIDTH   1920
#define DISP_HEIGHT  1080
#define BYTES_PER_PX 4
#define FB_SIZE      (DISP_WIDTH * DISP_HEIGHT * BYTES_PER_PX)

/* Place in DDR (align to 256-byte boundary required by DPDMA) */
static uint8_t __attribute__((aligned(256))) framebuf[FB_SIZE];

/* Simple LCG random — no stdlib in baremetal */
static uint32_t lcg_state = 0xDEADBEEF;
static uint8_t lcg_rand8(void)
{
    lcg_state = lcg_state * 1664525u + 1013904223u;
    return (uint8_t)(lcg_state >> 24);
}

static void fill_color(uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t *px = (uint32_t *)framebuf;
    /* BGRA layout expected by AVBuf RGB888 non-live mode */
    uint32_t color = ((uint32_t)0xFF << 24) |
                     ((uint32_t)r   << 16) |
                     ((uint32_t)g   <<  8) |
                      (uint32_t)b;

    for (int i = 0; i < DISP_WIDTH * DISP_HEIGHT; i++)
        px[i] = color;
}

int main(void)
{
    XDpPsu       dp = {0};
    XDpDma       dpdma;
    XAVBuf       avbuf;
    XDpPsu_Config *dp_cfg;
    XDpDma_Config *dma_cfg;
    XDpDma_FrameBuffer fb;
    int status;
    sleep(3);
    xil_printf("\r\n=== DP Hardware Detection ===\r\n");

    Xil_DCacheDisable();

    /* ----- DisplayPort init ----- */
    dp_cfg = XDpPsu_LookupConfig(XPAR_PSU_DP_DEVICE_ID);
    if (dp_cfg == NULL) {
        xil_printf("[FAIL] XDpPsu_LookupConfig returned NULL for 0x%08X\r\n",
                   XPAR_PSU_DP_DEVICE_ID);
        return 1;
    }
    xil_printf("[OK]   DP config found: BaseAddr=0x%08X\r\n", dp_cfg->BaseAddr);

    XDpPsu_CfgInitialize(&dp, dp_cfg, dp_cfg->BaseAddr);
    xil_printf("[OK]   XDpPsu_CfgInitialize done\r\n");

    status = XDpPsu_InitializeTx(&dp);
    xil_printf("[%s]   XDpPsu_InitializeTx: status=%d\r\n",
               status == XST_SUCCESS ? "OK  " : "WARN", status);

    /* Read HPD (Hot-Plug-Detect) raw signal from hardware register */
    {
        u32 hpd = XDpPsu_ReadReg(dp.Config.BaseAddr, XDPPSU_INTERRUPT_SIG_STATE);
        xil_printf("[INF]  HPD register=0x%08X  ->  display %s\r\n", hpd,
                   (hpd & XDPPSU_INTERRUPT_SIG_STATE_HPD_STATE_MASK)
                   ? "CONNECTED" : "NOT CONNECTED");
        
        if (hpd & XDPPSU_INTERRUPT_SIG_STATE_HPD_STATE_MASK) {
            msleep(100);  // Wait 100ms for monitor to stabilize
        }
    }

    status = XDpPsu_GetRxCapabilities(&dp);
    if (status != XST_SUCCESS) {
        xil_printf("[FAIL] GetRxCapabilities: %d  (no monitor or bad cable)\r\n", status);
        return 1;
    }
    xil_printf("[OK]   DPCD raw caps (bytes 0x00-0x0F):\r\n       ");
    for (int i = 0; i < 16; i++)
        xil_printf("%02X ", dp.RxConfig.DpcdRxCapsField[i]);
    xil_printf("\r\n");
    xil_printf("       [0]=DPrev [1]=MaxRate(06=1.62G/0A=2.7G/14=5.4G) [2]=MaxLanes\r\n");

    status = XDpPsu_CfgMainLinkMax(&dp);
    {
        const char *rate_str =
            (dp.LinkConfig.MaxLinkRate == 0x14) ? "5.4 Gbps HBR2" :
            (dp.LinkConfig.MaxLinkRate == 0x0A) ? "2.7 Gbps HBR"  :
            (dp.LinkConfig.MaxLinkRate == 0x06) ? "1.62 Gbps RBR" : "unknown";
        xil_printf("[%s]   CfgMainLinkMax: status=%d\r\n",
                   status == XST_SUCCESS ? "OK  " : "WARN", status);
        xil_printf("       MaxRate=0x%02X (%s)  MaxLanes=%d\r\n",
                   dp.LinkConfig.MaxLinkRate, rate_str, (int)dp.LinkConfig.MaxLaneCount);
        xil_printf("       ActiveRate=0x%02X  ActiveLanes=%d\r\n",
                   dp.LinkConfig.LinkRate, (int)dp.LinkConfig.LaneCount);
    }

    status = XDpPsu_EstablishLink(&dp);
    {
        u32 phy = XDpPsu_ReadReg(dp.Config.BaseAddr, XDPPSU_PHY_STATUS);
        xil_printf("[%s]   EstablishLink: status=%d  PHY_STATUS=0x%08X\r\n",
                   status == XST_SUCCESS ? "OK  " : "FAIL", status, phy);
        if (status != XST_SUCCESS) {
            xil_printf("[FAIL] Link training failed — halting\r\n");
            return 1;
        }
    }

    u8 edid[128];
    int retry;
    for (retry = 0; retry < 3; retry++) {
        status = XDpPsu_GetEdid(&dp, edid);
        if (status == XST_SUCCESS) {
            xil_printf("[OK]   EDID read successful on attempt %d\r\n", retry + 1);
            break;
        }
        usleep(50000);  // Wait 50ms between retries
    }

    if (status == XST_SUCCESS) {
        XDpPsu_CfgMsaUseEdidPreferredTiming(&dp, edid);
        XDpPsu_CfgMsaSetBpc(&dp, 8);
    } else {
        xil_printf("[WARN] EDID read failed after %d attempts, using fallback\r\n", retry);
        XDpPsu_CfgMsaSetBpc(&dp, 8);
        XDpPsu_CfgMsaUseStandardVideoMode(&dp, XVIDC_VM_1920x1080_60_P);
    }
    XDpPsu_SetVideoMode(&dp);
    xil_printf("[OK]   MSA: %dx%d @ %dHz  BPC=%d  PixClk=%dHz\r\n",
               (int)dp.MsaConfig.Vtm.Timing.HActive,
               (int)dp.MsaConfig.Vtm.Timing.VActive,
               (int)dp.MsaConfig.Vtm.FrameRate,
               (int)dp.MsaConfig.BitsPerColor,
               (int)dp.MsaConfig.PixelClockHz);

    /* ----- DPDMA init ----- */
    dma_cfg = XDpDma_LookupConfig(XPAR_PSU_DPDMA_DEVICE_ID);
    xil_printf("[OK]   DPDMA config: BaseAddr=0x%08X\r\n", dma_cfg->BaseAddr);
    XDpDma_CfgInitialize(&dpdma, dma_cfg);
    XDpDma_SetQOS(&dpdma, 11);
    XDpDma_SetGraphicsFormat(&dpdma, RGBA8888);   /* sets Gfx.VideoInfo — required by Trigger */
    XDpDma_SetChannelState(&dpdma, GraphicsChan, XDPDMA_ENABLE);

    /* ----- AVBuf init ----- */
    XAVBuf_CfgInitialize(&avbuf, XPAR_PSU_DP_DEVICE_ID);
    /* Use GRAPHICS stream (stream 2), not video stream 1 */
    XAVBuf_InputVideoSelect(&avbuf, XAVBUF_VIDSTREAM1_NONE,
                             XAVBUF_VIDSTREAM2_NONLIVE_GFX);
    XAVBuf_SetInputNonLiveGraphicsFormat(&avbuf, RGBA8888);
    XAVBuf_SetOutputVideoFormat(&avbuf, RGB_8BPC);
    XAVBuf_ConfigureGraphicsPipeline(&avbuf);
    XAVBuf_ConfigureOutputVideo(&avbuf);
    XAVBuf_SetBlenderAlpha(&avbuf, 0, 0);             /* pixel-based alpha */
    XAVBuf_EnableGraphicsBuffers(&avbuf, 1U);
    XAVBuf_SetAudioVideoClkSrc(&avbuf, XAVBUF_PS_CLK, XAVBUF_PS_CLK);
    XAVBuf_SoftReset(&avbuf);
    xil_printf("[OK]   AVBuf: graphics pipeline configured (RGBA8888 -> RGB_8BPC)\r\n");

    /* ----- Start DPDMA graphics channel ----- */
    fb.Address = (UINTPTR)framebuf;
    fb.Size    = FB_SIZE;
    fb.Stride  = DISP_WIDTH * BYTES_PER_PX;
    fb.LineSize = DISP_WIDTH * BYTES_PER_PX;
    fill_color(0, 0, 0);                          /* pre-fill black so first frame isn't garbage */
    XDpDma_DisplayGfxFrameBuffer(&dpdma, &fb);
    XDpDma_SetupChannel(&dpdma, GraphicsChan);
    XDpDma_Trigger(&dpdma, GraphicsChan);         /* actually writes to XDPDMA_GBL register */
    XDpPsu_EnableMainLink(&dp, 1U);
    /* EDID read via I2C-over-AUX */
    xil_printf("[DBG]  Attempting EDID read via I2C-over-AUX...\r\n");
    status = XDpPsu_GetEdid(&dp, edid);
    xil_printf("[DBG]  EDID status=%d (0=success, 2=timeout/no_device)\r\n", status);
    if (status == XST_SUCCESS) {
        xil_printf("[DBG]  EDID header: %02X %02X %02X %02X %02X %02X %02X %02X\r\n",
                edid[0], edid[1], edid[2], edid[3], 
                edid[4], edid[5], edid[6], edid[7]);
    xil_printf("[OK]   DMA triggered: FB=0x%08X  size=%d  stride=%d\r\n",
               (unsigned int)fb.Address, (int)fb.Size, (int)fb.Stride);
    xil_printf("=== Init complete — starting color loop ===\r\n");

    while (1) {
        uint8_t r = lcg_rand8();
        uint8_t g = lcg_rand8();
        uint8_t b = lcg_rand8();
        xil_printf("R=%3d G=%3d B=%3d\r\n", r, g, b);
        fill_color(r, g, b);
        /* Re-setup descriptor (same buffer address, updated content) then retrigger */
        XDpDma_DisplayGfxFrameBuffer(&dpdma, &fb);  /* sets RETRIGGER_EN flag */
        XDpDma_SetupChannel(&dpdma, GraphicsChan);  /* re-inits descriptor */
        XDpDma_ReTrigger(&dpdma, GraphicsChan);     /* writes hardware trigger */
        sleep(2);
    }

    return 0;
}