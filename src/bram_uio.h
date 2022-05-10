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
    BRAM(unsigned int uio_number, unsigned int size) {
        char device_file_name[20];
        sprintf(device_file_name, "/dev/uio%d", uio_number);

        int device_file;

        if ((device_file = open(device_file_name, O_RDWR | O_SYNC)) < 0) {
            std::stringstream ss;
            ss << device_file_name << " could not be opened";
            throw ss.str();
        }

        bram_ptr = (T *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, device_file, 0x0);

        if (bram_ptr == NULL) {
            std::stringstream ss;
            ss << "Could not map memory";
            throw ss.str();
        }
    }


    T& operator()(unsigned int) {
        return bram_ptr[index];
    }

private:
    T *bram_ptr;

};
