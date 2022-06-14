#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <pthread.h>

#include "../include/Q1.h"
#include "../include/Q2.h"

static void entryQ1(void);

static void entryQ2(void);

typedef void (*Entry)(void);

int main(int argc, char *argv[])
{
    Entry entries[] = {
        entryQ1, entryQ2
    };

    size_t choice;
    bool  flag      = true;
    while (flag)
    {
        printf("Please enter the solution number that you want to execute (from 1 to %zd, Ctrl+D to exit): ", sizeof(entries) / sizeof(Entry));
        if (scanf("%zd", &choice) != EOF)
        {
            if (choice > sizeof(entries) / sizeof(Entry) || choice < 1)
            {
                puts("Invalid number, please try again.");
                while (getchar() != '\n');
            }
            else
            {
                entries[choice - 1]();
            }
        }
        else
        {
            flag = false;
        }
    }

    return 0;
}

void entryQ1(void)
{
    pthread_t       thread;
    static uint32_t threadID = 0;
    uint32_t        bound;

    // Ask user for a bound of the list of prime numbers;
    bool            flag     = true;
    while (flag)
    {
        printf("Please enter the upper bound for the prime number list (greater than 1, Ctrl+D to exit): ");
        if (scanf("%" SCNu32, &bound) != EOF)
        {
            if (bound <= 1)
            {
                puts("Invalid number, please try again.");
                while (getchar() != '\n');
            }
            else
            {
                // Destruction of the structure is asynchronous, so we need to allocate it on heap.
                // The struct will be destroyed by the thread itself when the computation is done.
                ParameterQ1 *parameterQ1 = malloc(sizeof(ParameterQ1));

                parameterQ1->threadID = threadID++;
                parameterQ1->bound    = bound;

                pthread_create(&thread, NULL, runnerQ1, (void *) parameterQ1);
            }
        }
        else
        {
            flag = false;
        }
    }
}

void entryQ2(void)
{
    pthread_t       thread;
    static uint32_t threadID = 0;
    uint32_t        fibonacciCount;

    bool            flag     = true;
    while (flag)
    {
        printf("Please enter the number of elements of the Fibonacci list (greater than 1, Ctrl+D to exit): ");
        if (scanf("%" SCNu32, &fibonacciCount) != EOF)
        {
            if (fibonacciCount <= 1)
            {
                puts("Invalid number, please try again.");
                while (getchar() != '\n');
            }
            else
            {
                // Destruction of the structure is synchronous, so it is okay to allocate the struct on stack
                ParameterQ2 parameterQ2 = {
                    .threadID = threadID++, .fibonacciCount = fibonacciCount
                };

                pthread_create(&thread, NULL, runnerQ2, (void *) &parameterQ2);
                pthread_join(thread, NULL);

                printf("Fibonacci sequence: ");
                for (uint32_t i = 0; i < fibonacciCount; ++i)
                {
                    printf(" %" PRIu32, parameterQ2.result[i]);
                }
                putchar('\n');

                // Don't forget to free the memory allocated by the thread
                free(parameterQ2.result);
            }
        }
        else
        {
            flag = false;
        }
    }
}
