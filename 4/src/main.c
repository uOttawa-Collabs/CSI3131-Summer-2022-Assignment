#include <stdio.h>
#include <stdbool.h>

#include "Q2/Q2.h"
#include "Q3/Q3.h"

typedef void (*Entry)(void);

int main(int argc, char *argv[])
{
    size_t bias = 2;
    Entry entries[] = {
        entryQ2, entryQ3
    };

    size_t choice;
    bool  flag      = true;
    while (flag)
    {
        printf("Please enter the solution number that you want to execute (from %zd to %zd, Ctrl+D to exit): ", bias, sizeof(entries) / sizeof(Entry) + bias - 1);
        if (scanf("%zd", &choice) != EOF)
        {
            if (choice - bias >= sizeof(entries) / sizeof(Entry) || choice < bias)
            {
                puts("Invalid number, please try again.");
                while (getchar() != '\n');
            }
            else
            {
                entries[choice - bias]();
            }
        }
        else
        {
            flag = false;
        }
    }

    return 0;
}
