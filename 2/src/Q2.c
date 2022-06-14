#include "../include/Q2.h"

#include <stdio.h>
#include <malloc.h>
#include <pthread.h>

#define PRINT_PREFIX(TID) printf("[Thread %" PRIu32 "]", (TID))

void *runnerQ2(void *parameter)
{
    ParameterQ2 *parameterQ2 = (ParameterQ2 *) parameter;

    PRINT_PREFIX(parameterQ2->threadID);
    puts(" Start to generate fibonacci sequence");

    parameterQ2->result = calloc(parameterQ2->fibonacciCount, sizeof(uint32_t));
    parameterQ2->result[0] = 0;
    parameterQ2->result[1] = 1;

    for (uint32_t i = 2; i < parameterQ2->fibonacciCount; ++i)
    {
        parameterQ2->result[i] = parameterQ2->result[i - 1] + parameterQ2->result[i - 2];
    }

    PRINT_PREFIX(parameterQ2->threadID);
    puts(" Finished generating fibonacci sequence");
    pthread_exit(NULL);
}
