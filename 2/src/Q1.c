#include "../include/Q1.h"

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <pthread.h>

#define PRINT_PREFIX(TID) printf("\n[Thread %" PRIu32 "]", (TID))

static inline bool isPrime(uint32_t number)
{
    if (number == 2)
    {
        return true;
    }
    else if (number < 2 || !(number & 0x1))
    {
        return false;
    }
    else
    {
        for (uint32_t i = 2; i * i <= number; ++i)
        {
            if (!(number % i))
            {
                return false;
            }
        }
        return true;
    }
}

void *runnerQ1(void *parameter)
{
    ParameterQ1 *parameterQ1 = (ParameterQ1 *) parameter;

    PRINT_PREFIX(parameterQ1->threadID);

    for (int i = 2; i < parameterQ1->bound; ++i)
    {
        if (isPrime(i))
        {
            printf(" %" PRIu32, i);
        }
    }

    putchar('\n');
    free(parameter);
    pthread_exit(NULL);
}
