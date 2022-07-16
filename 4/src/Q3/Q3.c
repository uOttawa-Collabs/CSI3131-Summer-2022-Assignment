#include "Q3.h"

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "SharedMemory.h"
#include "CatalanNumber.h"

static uint8_t getUserInput(void);

void entryQ3(void)
{
    uint8_t n = getUserInput();

    SharedMemory *sharedMemory = createSharedMemory((n + 1) * sizeof(uint64_t));
    if (!sharedMemory)
    {
        fprintf(stderr, "Cannot create shared memory\n");
        return;
    }

    int pipeDescriptors[2];
    if (pipe(pipeDescriptors) < 0)
    {
        fprintf(stderr, "Cannot create pipe\n");
        return;
    }

    pid_t pid = fork();
    if (pid)
    {
        // Parent process: reader

        // Close the writing end for the parent
        close(pipeDescriptors[1]);

        // Block till child finishes calculate
        bool finished = false;
        read(pipeDescriptors[0], &finished, sizeof(bool));

        // Print out content of the shared memory
        for (size_t i = 1; i < sharedMemory->size / sizeof(uint64_t); ++i)
        {
            printf("%" PRIu64 "\n", ((uint64_t *)(sharedMemory->pointer))[i]);
        }

        // Clean up
        close(pipeDescriptors[0]);
        deleteSharedMemory(sharedMemory);
    }
    else
    {
        // Child process: writer

        // Close the reading end for the child
        close(pipeDescriptors[0]);

        // Generate Catalan Numbers
        generateCatalanNumbers((uint64_t *)sharedMemory->pointer, n + 1);

        // Notify parent process
        bool finished = true;
        write(pipeDescriptors[1], &finished, sizeof(bool));

        // Clean up and exit
        close(pipeDescriptors[1]);
        exit(0);
    }
}

uint8_t getUserInput(void)
{
    uint8_t n;

    for (;;)
    {
        printf("How many Catalan Numbers should be generated (<= 36)? ");
        if (scanf("%" SCNu8, &n) != EOF)
        {
            if (n > 36 || n < 1)
            {
                puts("Invalid number, please try again.");
                while (getchar() != '\n');
            }
            else
            {
                return n;
            }
        }
    }
}
