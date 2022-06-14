/* ------------------------------------------------ ------------
File: cpr.c

Name: Jake Wang
Student number: <redacted>

Description: This program contains the code for creation
of a child process and attach a pipe to it.
        The child will send messages through the pipe
        which will then be sent to standard output.

Explanation of the zombie process
(point 5 of "To be completed" in the assignment):

A terminated child process need to wait the parent reads the exit status
before being reaped from the process table.

Normally, the parent is not blocked for a long time, so it can immediately
read the exit status with the wait() system call. So the zombie state for a
child is transient.

But in our case, the parent is blocked by the sleep() system call and
cannot do anything before the timeout, including reading the child's exit
status, during which, the child is in the zombie state and continue to exist
in the process table until the parent in unblocked.
------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/select.h>
#include <sys/wait.h>

/*
* The size is guaranteed to be enough to contain any integer, since
* INT_MIN = -2 ^ 31 has maximum 10 digit and a sign.
*/
#define INT_STRING_MAX_LENGTH                       11
#define READ_BUFFER_SIZE                            32

#define FORMAT_STRING_PROCESS_BEGINS                "Process %d begins\n"
#define FORMAT_STRING_PROCESS_ENDS                  "Process %d ends\n"

/* Prototype */
void createChildAndRead(int);

static char *programName;

/* -------------------------------------------------------------
Function: main
Arguments: 
    int ac  - number of command arguments
    char **av - array of pointers to command arguments
Description:
    Extract the number of processes to be created from the
    Command line. If an error occurs, the process ends.
    Call createChildAndRead to create a child, and read
    the child's data.
-------------------------------------------------- ----------- */

int main(int ac, char **av)
{
    /*
    * Prototype of createChildAndRead() is given,
    * so global variables are used to pass program name to
    * createChildAndRead() function.
    */
    programName = av[0];

    int processNumber;

    if (ac == 2)
    {
        if (sscanf(av[1], "%d", &processNumber) == 1)
        {
            createChildAndRead(processNumber);
        }
        else
        {
            fprintf(stderr, "Cannot translate argument\n");
        }
    }
    else
    {
        fprintf(stderr, "Invalid arguments\n");
    }

    return 0;
}


/* ------------------------------------------------ -------------
Function: createChildAndRead
Arguments: 
    int prcNum - the process number
Description:
    Create the child, passing prcNum-1 to it. Use prcNum
    as the identifier of this process. Also, read the
    messages from the reading end of the pipe and sends it to
    the standard output (df 1). Finish when no data can
    be read from the pipe.
-------------------------------------------------- ----------- */

void createChildAndRead(int prcNum)
{
    char bufferBeginMessage[sizeof(FORMAT_STRING_PROCESS_BEGINS) + INT_STRING_MAX_LENGTH];
    char bufferEndMessage[sizeof(FORMAT_STRING_PROCESS_ENDS) + INT_STRING_MAX_LENGTH];

    // Prepare messages
    sprintf(bufferBeginMessage, FORMAT_STRING_PROCESS_BEGINS, prcNum);
    sprintf(bufferEndMessage, FORMAT_STRING_PROCESS_ENDS, prcNum);

    // Write start messages to the stdout
    // Note: In child, stdout is replaced with a pipe
    write(STDOUT_FILENO, bufferBeginMessage, strlen(bufferBeginMessage));

    int pipeDescriptors[2];
    if (prcNum > 1)
    {
        // Haven't reached the base case yet, continue forking
        if (pipe(pipeDescriptors) < 0)
        {
            fprintf(stderr, "Cannot create pipe\n");
            exit(EXIT_FAILURE);
        }

        pid_t pid = fork();
        if (pid < 0)
        {
            fprintf(stderr, "Cannot create child process\n");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            // Child starts

            // Close the reading end for the child
            close(pipeDescriptors[0]);

            /*
                * Here, replace stdout with the writing end of the pipe,
                * so all children will write to the pipe.
                */
            dup2(pipeDescriptors[1], STDOUT_FILENO);

            // Converting prcNum - 1 to a string
            char numberBuffer[INT_STRING_MAX_LENGTH + 1];
            sprintf(numberBuffer, "%d", prcNum - 1);

            // Calling exec to replace the child's code
            char *args[] = { programName, numberBuffer, NULL };
            execvp(programName, args);

            // Reaching here means execvp() failed
            fprintf(stderr, "Cannot execute program %s\n", programName);
            exit(EXIT_FAILURE);
        }
        else
        {
            // Parent starts

            // Close the writing end for the parent
            close(pipeDescriptors[1]);

            char bufferMessageFromChild[READ_BUFFER_SIZE];
            ssize_t count;
            while ((count = read(pipeDescriptors[0], bufferMessageFromChild, READ_BUFFER_SIZE)) > 0)
            {
                write(STDOUT_FILENO, bufferMessageFromChild, count);
            }
        }
    }
    else if (prcNum == 1)
    {
        // Reached base case
        sleep(5);
    }
    write(STDOUT_FILENO, bufferEndMessage, strlen(bufferEndMessage));
}
