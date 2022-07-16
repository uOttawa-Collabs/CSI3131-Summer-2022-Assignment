#include "CatalanNumber.h"

#include <stdio.h>

uint64_t *generateCatalanNumbers(uint64_t *array, uint8_t n)
{
    if (n > 37)
    {
        // Can't handle results that may cause overflow
        return NULL;
    }
    else if (array != NULL)
    {
        array[0] = 1;
        for (uint8_t i = 1; i < n; ++i)
        {
            array[i] = 0;
            for (uint8_t j = 0; j < i; ++j)
            {
                array[i] += array[j] * array[i - j - 1];
            }
        }
    }

    return array;
}
