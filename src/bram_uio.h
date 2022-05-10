// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#pragma once

//#ifdef __cplusplus
//extern "C" {
//#endif

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

#include <string>
#include <sstream>

/******************************** Class ***********************************/
template <class T = uint32_t>
class BRAM {

public:
    BRAM(unsigned int uio_number, unsigned int size);

    T& operator[](unsigned int);

private:
    uint32_t *bram_ptr;

};
