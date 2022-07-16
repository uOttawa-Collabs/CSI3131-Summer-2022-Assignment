#include "SharedMemory.h"

#include <stdlib.h>
#include <sys/mman.h>


SharedMemory *createSharedMemory(size_t size)
{
    SharedMemory *sharedMemory = malloc(sizeof(SharedMemory));
    sharedMemory->pointer = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (sharedMemory->pointer == MAP_FAILED)
    {
        free(sharedMemory);
        return NULL;
    }
    else
    {
        sharedMemory->size = size;
        return sharedMemory;
    }
}

int deleteSharedMemory(SharedMemory *sharedMemory)
{
    int result = munmap(sharedMemory->pointer, sharedMemory->size);
    if (!result)
    {
        free(sharedMemory);
    }
    return result;
}
