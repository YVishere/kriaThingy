// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.1 (64-bit)
// Tool Version Limit: 2025.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XISPPIPELINE_ACCEL_H
#define XISPPIPELINE_ACCEL_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xisppipeline_accel_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
#ifdef SDT
    char *Name;
#else
    u16 DeviceId;
#endif
    u64 Ctrl_BaseAddress;
} XIsppipeline_accel_Config;
#endif

typedef struct {
    u64 Ctrl_BaseAddress;
    u32 IsReady;
} XIsppipeline_accel;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XIsppipeline_accel_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XIsppipeline_accel_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XIsppipeline_accel_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XIsppipeline_accel_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
#ifdef SDT
int XIsppipeline_accel_Initialize(XIsppipeline_accel *InstancePtr, UINTPTR BaseAddress);
XIsppipeline_accel_Config* XIsppipeline_accel_LookupConfig(UINTPTR BaseAddress);
#else
int XIsppipeline_accel_Initialize(XIsppipeline_accel *InstancePtr, u16 DeviceId);
XIsppipeline_accel_Config* XIsppipeline_accel_LookupConfig(u16 DeviceId);
#endif
int XIsppipeline_accel_CfgInitialize(XIsppipeline_accel *InstancePtr, XIsppipeline_accel_Config *ConfigPtr);
#else
int XIsppipeline_accel_Initialize(XIsppipeline_accel *InstancePtr, const char* InstanceName);
int XIsppipeline_accel_Release(XIsppipeline_accel *InstancePtr);
#endif

void XIsppipeline_accel_Start(XIsppipeline_accel *InstancePtr);
u32 XIsppipeline_accel_IsDone(XIsppipeline_accel *InstancePtr);
u32 XIsppipeline_accel_IsIdle(XIsppipeline_accel *InstancePtr);
u32 XIsppipeline_accel_IsReady(XIsppipeline_accel *InstancePtr);
void XIsppipeline_accel_EnableAutoRestart(XIsppipeline_accel *InstancePtr);
void XIsppipeline_accel_DisableAutoRestart(XIsppipeline_accel *InstancePtr);

void XIsppipeline_accel_Set_common_config(XIsppipeline_accel *InstancePtr, u32 Data);
u32 XIsppipeline_accel_Get_common_config(XIsppipeline_accel *InstancePtr);
void XIsppipeline_accel_Set_awb_config(XIsppipeline_accel *InstancePtr, u32 Data);
u32 XIsppipeline_accel_Get_awb_config(XIsppipeline_accel *InstancePtr);
void XIsppipeline_accel_Set_blc_config_1(XIsppipeline_accel *InstancePtr, u32 Data);
u32 XIsppipeline_accel_Get_blc_config_1(XIsppipeline_accel *InstancePtr);
void XIsppipeline_accel_Set_blc_config_2(XIsppipeline_accel *InstancePtr, u32 Data);
u32 XIsppipeline_accel_Get_blc_config_2(XIsppipeline_accel *InstancePtr);
void XIsppipeline_accel_Set_gain_control_config_1(XIsppipeline_accel *InstancePtr, u32 Data);
u32 XIsppipeline_accel_Get_gain_control_config_1(XIsppipeline_accel *InstancePtr);
void XIsppipeline_accel_Set_gain_control_config_2(XIsppipeline_accel *InstancePtr, u32 Data);
u32 XIsppipeline_accel_Get_gain_control_config_2(XIsppipeline_accel *InstancePtr);
void XIsppipeline_accel_Set_resize_config(XIsppipeline_accel *InstancePtr, u32 Data);
u32 XIsppipeline_accel_Get_resize_config(XIsppipeline_accel *InstancePtr);
u32 XIsppipeline_accel_Get_pipeline_config_info(XIsppipeline_accel *InstancePtr);
u32 XIsppipeline_accel_Get_max_supported_size(XIsppipeline_accel *InstancePtr);
u32 XIsppipeline_accel_Get_funcs_available(XIsppipeline_accel *InstancePtr);
u32 XIsppipeline_accel_Get_funcs_bypassable(XIsppipeline_accel *InstancePtr);
void XIsppipeline_accel_Set_funcs_bypass_config(XIsppipeline_accel *InstancePtr, u32 Data);
u32 XIsppipeline_accel_Get_funcs_bypass_config(XIsppipeline_accel *InstancePtr);
u32 XIsppipeline_accel_Get_gamma_lut_BaseAddress(XIsppipeline_accel *InstancePtr);
u32 XIsppipeline_accel_Get_gamma_lut_HighAddress(XIsppipeline_accel *InstancePtr);
u32 XIsppipeline_accel_Get_gamma_lut_TotalBytes(XIsppipeline_accel *InstancePtr);
u32 XIsppipeline_accel_Get_gamma_lut_BitWidth(XIsppipeline_accel *InstancePtr);
u32 XIsppipeline_accel_Get_gamma_lut_Depth(XIsppipeline_accel *InstancePtr);
u32 XIsppipeline_accel_Write_gamma_lut_Words(XIsppipeline_accel *InstancePtr, int offset, word_type *data, int length);
u32 XIsppipeline_accel_Read_gamma_lut_Words(XIsppipeline_accel *InstancePtr, int offset, word_type *data, int length);
u32 XIsppipeline_accel_Write_gamma_lut_Bytes(XIsppipeline_accel *InstancePtr, int offset, char *data, int length);
u32 XIsppipeline_accel_Read_gamma_lut_Bytes(XIsppipeline_accel *InstancePtr, int offset, char *data, int length);
u32 XIsppipeline_accel_Get_ccm_config_1_BaseAddress(XIsppipeline_accel *InstancePtr);
u32 XIsppipeline_accel_Get_ccm_config_1_HighAddress(XIsppipeline_accel *InstancePtr);
u32 XIsppipeline_accel_Get_ccm_config_1_TotalBytes(XIsppipeline_accel *InstancePtr);
u32 XIsppipeline_accel_Get_ccm_config_1_BitWidth(XIsppipeline_accel *InstancePtr);
u32 XIsppipeline_accel_Get_ccm_config_1_Depth(XIsppipeline_accel *InstancePtr);
u32 XIsppipeline_accel_Write_ccm_config_1_Words(XIsppipeline_accel *InstancePtr, int offset, word_type *data, int length);
u32 XIsppipeline_accel_Read_ccm_config_1_Words(XIsppipeline_accel *InstancePtr, int offset, word_type *data, int length);
u32 XIsppipeline_accel_Write_ccm_config_1_Bytes(XIsppipeline_accel *InstancePtr, int offset, char *data, int length);
u32 XIsppipeline_accel_Read_ccm_config_1_Bytes(XIsppipeline_accel *InstancePtr, int offset, char *data, int length);
u32 XIsppipeline_accel_Get_ccm_config_2_BaseAddress(XIsppipeline_accel *InstancePtr);
u32 XIsppipeline_accel_Get_ccm_config_2_HighAddress(XIsppipeline_accel *InstancePtr);
u32 XIsppipeline_accel_Get_ccm_config_2_TotalBytes(XIsppipeline_accel *InstancePtr);
u32 XIsppipeline_accel_Get_ccm_config_2_BitWidth(XIsppipeline_accel *InstancePtr);
u32 XIsppipeline_accel_Get_ccm_config_2_Depth(XIsppipeline_accel *InstancePtr);
u32 XIsppipeline_accel_Write_ccm_config_2_Words(XIsppipeline_accel *InstancePtr, int offset, word_type *data, int length);
u32 XIsppipeline_accel_Read_ccm_config_2_Words(XIsppipeline_accel *InstancePtr, int offset, word_type *data, int length);
u32 XIsppipeline_accel_Write_ccm_config_2_Bytes(XIsppipeline_accel *InstancePtr, int offset, char *data, int length);
u32 XIsppipeline_accel_Read_ccm_config_2_Bytes(XIsppipeline_accel *InstancePtr, int offset, char *data, int length);

void XIsppipeline_accel_InterruptGlobalEnable(XIsppipeline_accel *InstancePtr);
void XIsppipeline_accel_InterruptGlobalDisable(XIsppipeline_accel *InstancePtr);
void XIsppipeline_accel_InterruptEnable(XIsppipeline_accel *InstancePtr, u32 Mask);
void XIsppipeline_accel_InterruptDisable(XIsppipeline_accel *InstancePtr, u32 Mask);
void XIsppipeline_accel_InterruptClear(XIsppipeline_accel *InstancePtr, u32 Mask);
u32 XIsppipeline_accel_InterruptGetEnabled(XIsppipeline_accel *InstancePtr);
u32 XIsppipeline_accel_InterruptGetStatus(XIsppipeline_accel *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
