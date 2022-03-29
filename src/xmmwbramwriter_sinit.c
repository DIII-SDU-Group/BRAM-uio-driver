// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xmmwbramwriter.h"

extern XMmwbramwriter_Config XMmwbramwriter_ConfigTable[];

XMmwbramwriter_Config *XMmwbramwriter_LookupConfig(u16 DeviceId) {
	XMmwbramwriter_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XMMWBRAMWRITER_NUM_INSTANCES; Index++) {
		if (XMmwbramwriter_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XMmwbramwriter_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XMmwbramwriter_Initialize(XMmwbramwriter *InstancePtr, u16 DeviceId) {
	XMmwbramwriter_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XMmwbramwriter_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XMmwbramwriter_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

