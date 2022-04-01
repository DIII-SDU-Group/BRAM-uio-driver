/***************************** Include Files *********************************/
#include "bram_uio.h"

/************************** Function Implementation *************************/

BRAM::BRAM(unsigned int uio_number, unsigned int size) {
    char *device_file_name[20];
    sprintf(device_file_name, "/dev/uio%d", uio_number);

    int device_file;

    if ((device_file = open(device_file_name, O_RDWR | O_SYNC)) < 0) {
        std::stringstream ss;
        ss << device_file_name << " could not be opened";
        throw std::to_string(ss);
    }

    bram_ptr = (uint32_t *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, device_file, 0x0);

    if (bram_ptr == NULL) {
        std::stringstream ss;
        ss << "Could not map memory";
        throw std::to_string(ss);
    }
}

uint32_t& BRAM::operator[](unsigned int index) {
    return bram_ptr[index];
}