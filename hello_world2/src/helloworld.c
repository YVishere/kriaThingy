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

    Xil_DCacheFlushRange((UINTPTR)framebuf, FB_SIZE);
}

int main(void)
{
    XDpPsu       dp;
    XDpDma       dpdma;
    XAVBuf       avbuf;
    XDpPsu_Config *dp_cfg;
    XDpDma_Config *dma_cfg;
    XDpDma_FrameBuffer fb;
    int status;

    xil_printf("Hello================");

    Xil_DCacheEnable();

    /* ----- DisplayPort init ----- */
    dp_cfg = XDpPsu_LookupConfig(XPAR_PSU_DP_DEVICE_ID);
    XDpPsu_CfgInitialize(&dp, dp_cfg, dp_cfg->BaseAddr);

    status = XDpPsu_InitializeTx(&dp);
    if (status != XST_SUCCESS) {
        xil_printf("DP init failed: %d\r\n", status);
        return 1;
    }

    /* Set 1080p60 video timing */
    XDpPsu_CfgMsaUseStandardVideoMode(&dp, XVIDC_VM_1920x1080_60_P);
    XDpPsu_SetVideoMode(&dp);

    /* ----- DPDMA init ----- */
    dma_cfg = XDpDma_LookupConfig(XPAR_PSU_DPDMA_DEVICE_ID);
    XDpDma_CfgInitialize(&dpdma, dma_cfg);
    XDpDma_SetQOS(&dpdma, 11);

    /* ----- AVBuf init ----- */
    XAVBuf_CfgInitialize(&avbuf, XPAR_PSU_DP_DEVICE_ID);
    XAVBuf_InputVideoSelect(&avbuf, XAVBUF_VIDSTREAM1_NONLIVE,
                            XAVBUF_VIDSTREAM2_NONE);
    XAVBuf_SetInputNonLiveVideoFormat(&avbuf, RGBA8880);
    XAVBuf_SetOutputVideoFormat(&avbuf, RGB888);
    XAVBuf_ConfigureVideoPipeline(&avbuf);
    XAVBuf_ConfigureOutputVideo(&avbuf);

    XAVBuf_EnableVideoBuffers(&avbuf, 1U);

    /* ----- Start DPDMA graphics channel ----- */
    fb.Address = (UINTPTR)framebuf;
    fb.Size    = FB_SIZE;
    fb.Stride  = DISP_WIDTH * BYTES_PER_PX;
    XDpDma_DisplayGfxFrameBuffer(&dpdma, &fb);

    XDpPsu_EnableMainLink(&dp, 1U);


    while (1) {
        uint8_t r = lcg_rand8();
        uint8_t g = lcg_rand8();
        uint8_t b = lcg_rand8();

        xil_printf("R=%3d G=%3d B=%3d (#%02X%02X%02X)\r\n",
                   r, g, b, r, g, b);
        fill_color(r, g, b);
        sleep(1);
    }

    return 0;
}