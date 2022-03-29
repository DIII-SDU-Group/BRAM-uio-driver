/***************************** Include Files *********************************/
#include "bram_uio.h"

/************************** Function Implementation *************************/

int uio_read_map_size(int uio_number) {
    int ret;
    char file[ MAX_UIO_PATH_SIZE ];
    sprintf(file, "/sys/class/uio/uio%d/maps/map0/size", uio_number);
    FILE* fp = fopen(file, "r");
    if (!fp) return -1;
    int size;
    ret = fscanf(fp, "0x%x", &size);
    fclose(fp);
    if (ret < 0) return -2;
    return size;
}


void Xbram_write(Xbram *InstacePtr, int offset, int n_words, uint32_t *data) {

    for (int i = 0; i < n_words; i++) {

        Xbram_WriteReg(InstacePtr->Control_BaseAddress, offset+i, data[i]);

    }
}

void Xbram_read(Xbram *InstacePtr, int offset, int n_words, uint32_t *data) {

    for (int i = 0; i < n_words; i++) {

        data[i] = Xbram_ReadReg(InstacePtr->Control_BaseAddress, offset+i);

    }
}

int Xbram_Initialize(Xbram *InstancePtr, const int uio_number) {
    assert(InstancePtr != NULL);

    char device_file[ MAX_UIO_PATH_SIZE ];

    sprintf(device_file, "/dev/uio%d", uio_number);

    int uio_fd;

    if (uio_fd = open(device_file, O_RDWR)) < 0) {
        return XST_OPEN_DEVICE_FAILED;
    }

    int size = uio_read_map_size(uio_number);

    // NOTE: slave interface 'Control' should be mapped to uioX/map0
    InstancePtr->Control_BaseAddress = (u64)mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, uio_fd, 0 * getpagesize());
    assert(InstancePtr->Control_BaseAddress);

    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}