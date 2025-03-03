#include <stdio.h> // I have to get better at knowing what I actually need as an include
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    char buffer[80];
    while (1)
    {
        printf("Enter the program name\n");
        int ret = read(0, buffer, 80);

        char *ptr = buffer;
        char *ptr2 = buffer;
        int i = 0;
        char *arg[3];

        while (*ptr != '\n')
        {
            // arg[i] = *ptr;

            if (*ptr == ' ')
            {
                *ptr = '\0';
                arg[i] = ptr2;
                i++;
                ptr2 = ptr + 1;
                break;
            }
            ptr++;
        }
        *ptr = '\0';
        arg[i] = ptr2;
        arg[i + 1] = NULL;

        printf("Program name: %s\nParamater name: %s\n", arg[0], arg[1]);

        // NOW WE CAN CALL FORK AND DO THE REST!

        //     int pidd = fork();

        //     if (pidd == 0)
        //     { // if its the child?

        //         printf("Program name: %s\n", buffer);
        //         char *arg[] = {buffer, NULL}; // Sets up the vector array?

        //         execv(buffer, arg);
        //         printf("If I'm still here then there is a problem!\n");
        //         exit(1); // Terminates the CURRENT child - not the entire program
        //     }
        //     else
        //     {
        //         wait(0);
        //     }
    }
}
