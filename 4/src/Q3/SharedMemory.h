#ifndef INC_4_SHAREDMEMORY_H
#define INC_4_SHAREDMEMORY_H

#include <stdlib.h>

typedef struct
{
    void *pointer;
    size_t size;
} SharedMemory;

SharedMemory *createSharedMemory(size_t size);
int deleteSharedMemory(SharedMemory *sharedMemory);

#endif //INC_4_SHAREDMEMORY_H
