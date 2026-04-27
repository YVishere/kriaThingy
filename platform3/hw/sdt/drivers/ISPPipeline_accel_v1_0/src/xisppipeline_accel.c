// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.1 (64-bit)
// Tool Version Limit: 2025.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xisppipeline_accel.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XIsppipeline_accel_CfgInitialize(XIsppipeline_accel *InstancePtr, XIsppipeline_accel_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Ctrl_BaseAddress = ConfigPtr->Ctrl_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XIsppipeline_accel_Start(XIsppipeline_accel *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIsppipeline_accel_ReadReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_AP_CTRL) & 0x80;
    XIsppipeline_accel_WriteReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XIsppipeline_accel_IsDone(XIsppipeline_accel *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIsppipeline_accel_ReadReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XIsppipeline_accel_IsIdle(XIsppipeline_accel *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIsppipeline_accel_ReadReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XIsppipeline_accel_IsReady(XIsppipeline_accel *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIsppipeline_accel_ReadReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XIsppipeline_accel_EnableAutoRestart(XIsppipeline_accel *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIsppipeline_accel_WriteReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_AP_CTRL, 0x80);
}

void XIsppipeline_accel_DisableAutoRestart(XIsppipeline_accel *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIsppipeline_accel_WriteReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_AP_CTRL, 0);
}

void XIsppipeline_accel_Set_common_config(XIsppipeline_accel *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIsppipeline_accel_WriteReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_COMMON_CONFIG_DATA, Data);
}

u32 XIsppipeline_accel_Get_common_config(XIsppipeline_accel *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIsppipeline_accel_ReadReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_COMMON_CONFIG_DATA);
    return Data;
}

void XIsppipeline_accel_Set_awb_config(XIsppipeline_accel *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIsppipeline_accel_WriteReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_AWB_CONFIG_DATA, Data);
}

u32 XIsppipeline_accel_Get_awb_config(XIsppipeline_accel *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIsppipeline_accel_ReadReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_AWB_CONFIG_DATA);
    return Data;
}

void XIsppipeline_accel_Set_blc_config_1(XIsppipeline_accel *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIsppipeline_accel_WriteReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_BLC_CONFIG_1_DATA, Data);
}

u32 XIsppipeline_accel_Get_blc_config_1(XIsppipeline_accel *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIsppipeline_accel_ReadReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_BLC_CONFIG_1_DATA);
    return Data;
}

void XIsppipeline_accel_Set_blc_config_2(XIsppipeline_accel *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIsppipeline_accel_WriteReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_BLC_CONFIG_2_DATA, Data);
}

u32 XIsppipeline_accel_Get_blc_config_2(XIsppipeline_accel *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIsppipeline_accel_ReadReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_BLC_CONFIG_2_DATA);
    return Data;
}

void XIsppipeline_accel_Set_gain_control_config_1(XIsppipeline_accel *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIsppipeline_accel_WriteReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_GAIN_CONTROL_CONFIG_1_DATA, Data);
}

u32 XIsppipeline_accel_Get_gain_control_config_1(XIsppipeline_accel *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIsppipeline_accel_ReadReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_GAIN_CONTROL_CONFIG_1_DATA);
    return Data;
}

void XIsppipeline_accel_Set_gain_control_config_2(XIsppipeline_accel *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIsppipeline_accel_WriteReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_GAIN_CONTROL_CONFIG_2_DATA, Data);
}

u32 XIsppipeline_accel_Get_gain_control_config_2(XIsppipeline_accel *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIsppipeline_accel_ReadReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_GAIN_CONTROL_CONFIG_2_DATA);
    return Data;
}

void XIsppipeline_accel_Set_resize_config(XIsppipeline_accel *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIsppipeline_accel_WriteReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_RESIZE_CONFIG_DATA, Data);
}

u32 XIsppipeline_accel_Get_resize_config(XIsppipeline_accel *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIsppipeline_accel_ReadReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_RESIZE_CONFIG_DATA);
    return Data;
}

u32 XIsppipeline_accel_Get_pipeline_config_info(XIsppipeline_accel *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIsppipeline_accel_ReadReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_PIPELINE_CONFIG_INFO_DATA);
    return Data;
}

u32 XIsppipeline_accel_Get_max_supported_size(XIsppipeline_accel *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIsppipeline_accel_ReadReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_MAX_SUPPORTED_SIZE_DATA);
    return Data;
}

u32 XIsppipeline_accel_Get_funcs_available(XIsppipeline_accel *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIsppipeline_accel_ReadReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_FUNCS_AVAILABLE_DATA);
    return Data;
}

u32 XIsppipeline_accel_Get_funcs_bypassable(XIsppipeline_accel *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIsppipeline_accel_ReadReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_FUNCS_BYPASSABLE_DATA);
    return Data;
}

void XIsppipeline_accel_Set_funcs_bypass_config(XIsppipeline_accel *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIsppipeline_accel_WriteReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_FUNCS_BYPASS_CONFIG_DATA, Data);
}

u32 XIsppipeline_accel_Get_funcs_bypass_config(XIsppipeline_accel *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIsppipeline_accel_ReadReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_FUNCS_BYPASS_CONFIG_DATA);
    return Data;
}

u32 XIsppipeline_accel_Get_gamma_lut_BaseAddress(XIsppipeline_accel *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Ctrl_BaseAddress + XISPPIPELINE_ACCEL_CTRL_ADDR_GAMMA_LUT_BASE);
}

u32 XIsppipeline_accel_Get_gamma_lut_HighAddress(XIsppipeline_accel *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Ctrl_BaseAddress + XISPPIPELINE_ACCEL_CTRL_ADDR_GAMMA_LUT_HIGH);
}

u32 XIsppipeline_accel_Get_gamma_lut_TotalBytes(XIsppipeline_accel *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XISPPIPELINE_ACCEL_CTRL_ADDR_GAMMA_LUT_HIGH - XISPPIPELINE_ACCEL_CTRL_ADDR_GAMMA_LUT_BASE + 1);
}

u32 XIsppipeline_accel_Get_gamma_lut_BitWidth(XIsppipeline_accel *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XISPPIPELINE_ACCEL_CTRL_WIDTH_GAMMA_LUT;
}

u32 XIsppipeline_accel_Get_gamma_lut_Depth(XIsppipeline_accel *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XISPPIPELINE_ACCEL_CTRL_DEPTH_GAMMA_LUT;
}

u32 XIsppipeline_accel_Write_gamma_lut_Words(XIsppipeline_accel *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XISPPIPELINE_ACCEL_CTRL_ADDR_GAMMA_LUT_HIGH - XISPPIPELINE_ACCEL_CTRL_ADDR_GAMMA_LUT_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Ctrl_BaseAddress + XISPPIPELINE_ACCEL_CTRL_ADDR_GAMMA_LUT_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XIsppipeline_accel_Read_gamma_lut_Words(XIsppipeline_accel *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XISPPIPELINE_ACCEL_CTRL_ADDR_GAMMA_LUT_HIGH - XISPPIPELINE_ACCEL_CTRL_ADDR_GAMMA_LUT_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Ctrl_BaseAddress + XISPPIPELINE_ACCEL_CTRL_ADDR_GAMMA_LUT_BASE + (offset + i)*4);
    }
    return length;
}

u32 XIsppipeline_accel_Write_gamma_lut_Bytes(XIsppipeline_accel *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XISPPIPELINE_ACCEL_CTRL_ADDR_GAMMA_LUT_HIGH - XISPPIPELINE_ACCEL_CTRL_ADDR_GAMMA_LUT_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Ctrl_BaseAddress + XISPPIPELINE_ACCEL_CTRL_ADDR_GAMMA_LUT_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XIsppipeline_accel_Read_gamma_lut_Bytes(XIsppipeline_accel *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XISPPIPELINE_ACCEL_CTRL_ADDR_GAMMA_LUT_HIGH - XISPPIPELINE_ACCEL_CTRL_ADDR_GAMMA_LUT_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Ctrl_BaseAddress + XISPPIPELINE_ACCEL_CTRL_ADDR_GAMMA_LUT_BASE + offset + i);
    }
    return length;
}

u32 XIsppipeline_accel_Get_ccm_config_1_BaseAddress(XIsppipeline_accel *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Ctrl_BaseAddress + XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_1_BASE);
}

u32 XIsppipeline_accel_Get_ccm_config_1_HighAddress(XIsppipeline_accel *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Ctrl_BaseAddress + XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_1_HIGH);
}

u32 XIsppipeline_accel_Get_ccm_config_1_TotalBytes(XIsppipeline_accel *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_1_HIGH - XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_1_BASE + 1);
}

u32 XIsppipeline_accel_Get_ccm_config_1_BitWidth(XIsppipeline_accel *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XISPPIPELINE_ACCEL_CTRL_WIDTH_CCM_CONFIG_1;
}

u32 XIsppipeline_accel_Get_ccm_config_1_Depth(XIsppipeline_accel *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XISPPIPELINE_ACCEL_CTRL_DEPTH_CCM_CONFIG_1;
}

u32 XIsppipeline_accel_Write_ccm_config_1_Words(XIsppipeline_accel *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_1_HIGH - XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_1_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Ctrl_BaseAddress + XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_1_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XIsppipeline_accel_Read_ccm_config_1_Words(XIsppipeline_accel *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_1_HIGH - XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_1_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Ctrl_BaseAddress + XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_1_BASE + (offset + i)*4);
    }
    return length;
}

u32 XIsppipeline_accel_Write_ccm_config_1_Bytes(XIsppipeline_accel *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_1_HIGH - XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_1_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Ctrl_BaseAddress + XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_1_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XIsppipeline_accel_Read_ccm_config_1_Bytes(XIsppipeline_accel *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_1_HIGH - XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_1_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Ctrl_BaseAddress + XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_1_BASE + offset + i);
    }
    return length;
}

u32 XIsppipeline_accel_Get_ccm_config_2_BaseAddress(XIsppipeline_accel *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Ctrl_BaseAddress + XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_2_BASE);
}

u32 XIsppipeline_accel_Get_ccm_config_2_HighAddress(XIsppipeline_accel *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Ctrl_BaseAddress + XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_2_HIGH);
}

u32 XIsppipeline_accel_Get_ccm_config_2_TotalBytes(XIsppipeline_accel *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_2_HIGH - XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_2_BASE + 1);
}

u32 XIsppipeline_accel_Get_ccm_config_2_BitWidth(XIsppipeline_accel *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XISPPIPELINE_ACCEL_CTRL_WIDTH_CCM_CONFIG_2;
}

u32 XIsppipeline_accel_Get_ccm_config_2_Depth(XIsppipeline_accel *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XISPPIPELINE_ACCEL_CTRL_DEPTH_CCM_CONFIG_2;
}

u32 XIsppipeline_accel_Write_ccm_config_2_Words(XIsppipeline_accel *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_2_HIGH - XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_2_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Ctrl_BaseAddress + XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_2_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XIsppipeline_accel_Read_ccm_config_2_Words(XIsppipeline_accel *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_2_HIGH - XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_2_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Ctrl_BaseAddress + XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_2_BASE + (offset + i)*4);
    }
    return length;
}

u32 XIsppipeline_accel_Write_ccm_config_2_Bytes(XIsppipeline_accel *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_2_HIGH - XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_2_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Ctrl_BaseAddress + XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_2_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XIsppipeline_accel_Read_ccm_config_2_Bytes(XIsppipeline_accel *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_2_HIGH - XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_2_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Ctrl_BaseAddress + XISPPIPELINE_ACCEL_CTRL_ADDR_CCM_CONFIG_2_BASE + offset + i);
    }
    return length;
}

void XIsppipeline_accel_InterruptGlobalEnable(XIsppipeline_accel *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIsppipeline_accel_WriteReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_GIE, 1);
}

void XIsppipeline_accel_InterruptGlobalDisable(XIsppipeline_accel *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIsppipeline_accel_WriteReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_GIE, 0);
}

void XIsppipeline_accel_InterruptEnable(XIsppipeline_accel *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XIsppipeline_accel_ReadReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_IER);
    XIsppipeline_accel_WriteReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_IER, Register | Mask);
}

void XIsppipeline_accel_InterruptDisable(XIsppipeline_accel *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XIsppipeline_accel_ReadReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_IER);
    XIsppipeline_accel_WriteReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_IER, Register & (~Mask));
}

void XIsppipeline_accel_InterruptClear(XIsppipeline_accel *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIsppipeline_accel_WriteReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_ISR, Mask);
}

u32 XIsppipeline_accel_InterruptGetEnabled(XIsppipeline_accel *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XIsppipeline_accel_ReadReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_IER);
}

u32 XIsppipeline_accel_InterruptGetStatus(XIsppipeline_accel *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XIsppipeline_accel_ReadReg(InstancePtr->Ctrl_BaseAddress, XISPPIPELINE_ACCEL_CTRL_ADDR_ISR);
}

