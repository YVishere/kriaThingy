// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.1 (64-bit)
// Tool Version Limit: 2025.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
// CTRL
// 0x0000 : Control signals
//          bit 0  - ap_start (Read/Write/COH)
//          bit 1  - ap_done (Read/COR)
//          bit 2  - ap_idle (Read)
//          bit 3  - ap_ready (Read/COR)
//          bit 7  - auto_restart (Read/Write)
//          bit 9  - interrupt (Read)
//          others - reserved
// 0x0004 : Global Interrupt Enable Register
//          bit 0  - Global Interrupt Enable (Read/Write)
//          others - reserved
// 0x0008 : IP Interrupt Enable Register (Read/Write)
//          bit 0 - enable ap_done interrupt (Read/Write)
//          bit 1 - enable ap_ready interrupt (Read/Write)
//          others - reserved
// 0x000c : IP Interrupt Status Register (Read/TOW)
//          bit 0 - ap_done (Read/TOW)
//          bit 1 - ap_ready (Read/TOW)
//          others - reserved
// 0x0010 : Data signal of common_config
//          bit 31~0 - common_config[31:0] (Read/Write)
// 0x0014 : reserved
// 0x0020 : Data signal of awb_config
//          bit 31~0 - awb_config[31:0] (Read/Write)
// 0x0024 : reserved
// 0x0028 : Data signal of blc_config_1
//          bit 31~0 - blc_config_1[31:0] (Read/Write)
// 0x002c : reserved
// 0x0030 : Data signal of blc_config_2
//          bit 31~0 - blc_config_2[31:0] (Read/Write)
// 0x0034 : reserved
// 0x0038 : Data signal of gain_control_config_1
//          bit 31~0 - gain_control_config_1[31:0] (Read/Write)
// 0x003c : reserved
// 0x0040 : Data signal of gain_control_config_2
//          bit 31~0 - gain_control_config_2[31:0] (Read/Write)
// 0x0044 : reserved
// 0x0078 : Data signal of resize_config
//          bit 31~0 - resize_config[31:0] (Read/Write)
// 0x007c : reserved
// 0x0080 : Data signal of pipeline_config_info
//          bit 31~0 - pipeline_config_info[31:0] (Read)
// 0x0084 : reserved
// 0x0090 : Data signal of max_supported_size
//          bit 31~0 - max_supported_size[31:0] (Read)
// 0x0094 : reserved
// 0x00a0 : Data signal of funcs_available
//          bit 31~0 - funcs_available[31:0] (Read)
// 0x00a4 : reserved
// 0x00b0 : Data signal of funcs_bypassable
//          bit 31~0 - funcs_bypassable[31:0] (Read)
// 0x00b4 : reserved
// 0x00c0 : Data signal of funcs_bypass_config
//          bit 31~0 - funcs_bypass_config[31:0] (Read/Write)
// 0x00c4 : reserved
// 0x2000 ~
// 0x23ff : Memory 'gamma_lut' (768 * 8b)
//          Word n : bit [ 7: 0] - gamma_lut[4n]
//                   bit [15: 8] - gamma_lut[4n+1]
//                   bit [23:16] - gamma_lut[4n+2]
//                   bit [31:24] - gamma_lut[4n+3]
// 0x4000 ~
// 0x403f : Memory 'ccm_config_1' (9 * 32b)
//          Word n : bit [31:0] - ccm_config_1[n]
// 0x4100 ~
// 0x410f : Memory 'ccm_config_2' (3 * 32b)
//          Word n : bit [31:0] - ccm_config_2[n]
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XISPPIPELINE_ACCEL_CTRL_ADDR_AP_CTRL                    0x0000
#define XISPPIPELINE_ACCEL_CTRL_ADDR_GIE                        0x0004
#define XISPPIPELINE_ACCEL_CTRL_ADDR_IER                        0x0008
#define XISPPIPELINE_ACCEL_CTRL_ADDR_ISR                        0x000c
#define XISPPIPELINE_ACCEL_CTRL_ADDR_COMMON_CONFIG_DATA         0x0010
#define XISPPIPELINE_ACCEL_CTRL_BITS_COMMON_CONFIG_DATA         32
#define XISPPIPELINE_ACCEL_CTRL_ADDR_AWB_CONFIG_DATA            0x0020
#define XISPPIPELINE_ACCEL_CTRL_BITS_AWB_CONFIG_DATA            32
#define XISPPIPELINE_ACCEL_CTRL_ADDR_BLC_CONFIG_1_DATA          0x0028
#define XISPPIPELINE_ACCEL_CTRL_BITS_BLC_CONFIG_1_DATA          32
#define XISPPIPELINE_ACCEL_CTRL_ADDR_BLC_CONFIG_2_DATA          0x0030
#define XISPPIPELINE_ACCEL_CTRL_BITS_BLC_CONFIG_2_DATA          32
#define XISPPIPELINE_ACCEL_CTRL_ADDR_GAIN_CONTROL_CONFIG_1_DATA 0x0038
#define XISPPIPELINE_ACCEL_CTRL_BITS_GAIN_CONTROL_CONFIG_1_DATA 32
#define XISPPIPELINE_ACCEL_CTRL_ADDR_GAIN_CONTROL_CONFIG_2_DATA 0x0040
#define XISPPIPELINE_ACCEL_CTRL_BITS_GAIN_CONTROL_CONFIG_2_DATA 32
#define XISPPIPELINE_ACCEL_CTRL_ADDR_RESIZE_CONFIG_DATA         0x0078
#define XISPPIPELINE_ACCEL_CTRL_BITS_RESIZE_CONFIG_DATA         32
#define XISPPIPELINE_ACCEL_CTRL_ADDR_PIPELINE_CONFIG_INFO_DATA  0x0080
#define XISPPIPELINE_ACCEL_CTRL_BITS_PIPELINE_CONFIG_INFO_DATA  32
#define XISPPIPELINE_ACCEL_CTRL_ADDR_MAX_SUPPORTED_SIZE_DATA    0x0090
#define XISPPIPELINE_ACCEL_CTRL_BITS_MAX_SUPPORTED_SIZE_DATA    32
#define XISPPIPELINE_ACCEL_CTRL_ADDR_FUNCS_AVAILABLE_DATA       0x00a0
#define XISPPIPELINE_ACCEL_CTRL_BITS_FUNCS_AVAILABLE_DATA       32
#define XISPPIPELINE_ACCEL_CTRL_ADDR_FUNCS_BYPASSABLE_DATA      0x00b0
#define XISPPIPELINE_ACCEL_CTRL_BITS_FUNCS_BYPASSABLE_DATA      32
#define XISPPIPELINE_ACCEL_CTRL_ADDR_FUNCS_BYPASS_CONFIG_DATA   0x00c0
#define XISPPIPELINE_ACCEL_CTRL_BITS_FUNCS_BYPASS_CONFIG_DATA   32
#define XISPPIPELINE_ACCEL_CTRL_ADDR_GAMMA_LUT_BASE             0x2000
#define XISPPIPELINE_ACCEL_CTRL_ADDR_GAMMA_LUT_HIGH             0x23ff
#define XISPPIPELINE_ACCEL_CTRL_WIDTH_GAMMA_LUT                 8
#define XISPPIPELINE_ACCEL_CTRL_DEPTH_GAMMA_LUT                 768
#define XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_1_BASE          0x4000
#define XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_1_HIGH          0x403f
#define XISPPIPELINE_ACCEL_CTRL_WIDTH_CCM_CONFIG_1              32
#define XISPPIPELINE_ACCEL_CTRL_DEPTH_CCM_CONFIG_1              9
#define XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_2_BASE          0x4100
#define XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_2_HIGH          0x410f
#define XISPPIPELINE_ACCEL_CTRL_WIDTH_CCM_CONFIG_2              32
#define XISPPIPELINE_ACCEL_CTRL_DEPTH_CCM_CONFIG_2              3

