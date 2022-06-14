#ifndef Q1_H
#define Q1_H

#include <inttypes.h>

typedef struct
{
    uint32_t threadID;
    uint32_t bound;
} ParameterQ1;

void *runnerQ1(void *parameter);

#endif
