// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef BRAM_H
#define BRAM_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
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

/**************************** Type Definitions ******************************/

#define MAX_UIO_PATH_SIZE       256
#define MAX_UIO_NAME_SIZE       64

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} Xbram;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#define Xbram_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define Xbram_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1

/************************** Function Prototypes *****************************/
int Xbram_Initialize(Xbram *InstancePtr, const char* device_file);
int Xbram_Release(Xbram *InstancePtr);
void Xbram_write(Xbram *InstacePtr, int offset, int length, uint32_t *data);
void Xbram_read(Xbram *InstacePtr, int offset, int length, uint32_t *data);

#ifdef __cplusplus
}
#endif

#endif
