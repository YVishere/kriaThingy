// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.1 (64-bit)
// Tool Version Limit: 2025.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#ifdef SDT
#include "xparameters.h"
#endif
#include "xisppipeline_accel.h"

extern XIsppipeline_accel_Config XIsppipeline_accel_ConfigTable[];

#ifdef SDT
XIsppipeline_accel_Config *XIsppipeline_accel_LookupConfig(UINTPTR BaseAddress) {
	XIsppipeline_accel_Config *ConfigPtr = NULL;

	int Index;

	for (Index = (u32)0x0; XIsppipeline_accel_ConfigTable[Index].Name != NULL; Index++) {
		if (!BaseAddress || XIsppipeline_accel_ConfigTable[Index].Ctrl_BaseAddress == BaseAddress) {
			ConfigPtr = &XIsppipeline_accel_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XIsppipeline_accel_Initialize(XIsppipeline_accel *InstancePtr, UINTPTR BaseAddress) {
	XIsppipeline_accel_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XIsppipeline_accel_LookupConfig(BaseAddress);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XIsppipeline_accel_CfgInitialize(InstancePtr, ConfigPtr);
}
#else
XIsppipeline_accel_Config *XIsppipeline_accel_LookupConfig(u16 DeviceId) {
	XIsppipeline_accel_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XISPPIPELINE_ACCEL_NUM_INSTANCES; Index++) {
		if (XIsppipeline_accel_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XIsppipeline_accel_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XIsppipeline_accel_Initialize(XIsppipeline_accel *InstancePtr, u16 DeviceId) {
	XIsppipeline_accel_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XIsppipeline_accel_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XIsppipeline_accel_CfgInitialize(InstancePtr, ConfigPtr);
}
#endif

#endif

