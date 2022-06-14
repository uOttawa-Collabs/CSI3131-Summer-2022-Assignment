#ifndef Q2_H
#define Q2_H

#include <inttypes.h>

typedef struct
{
    uint32_t threadID;
    uint32_t fibonacciCount;
    uint32_t *result;
} ParameterQ2;

void *runnerQ2(void *parameter);

#endif
