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
        char *arg[4];

        while (*ptr != '\n')
        {
            // arg[i] = *ptr;

            if (*ptr == ' ')
            {
                *ptr = '\0';
                arg[i] = ptr2;
                i++;
                ptr2 = ptr + 1;
            }
            ptr++;
        }
        *ptr = '\0';
        arg[i] = ptr2;
        arg[i + 1] = NULL;

        printf("Program name: %s\nParamater name: %s\n", arg[0], arg[1]);
        // printf("%s\n", arg[2]);

        int counter = 0;

        for (char **i = arg; *i != NULL; i++)
        {
            printf("Counter: %d\n", counter);
            counter++;
        }

        printf("Counter outside loop: %d", counter);

        if (counter == 1)
        {
            printf("Getting ready to execute Program name: %s\n", arg[0]);
        }

        else if (counter == 2)
        {
            printf("Getting ready to execute Program name %s, with Parameter: %s\n", arg[0], arg[1]);
        }

        else if (counter == 3)
        {
            printf("Getting ready to execute Program name %s, with parameters %s and %s\n", arg[0], arg[1], arg[2]);
        }

        else if (counter == 4)
        {
            printf("Getting ready to execute Program name %s, with parameters %s and %s and %s\n", arg[0], arg[1], arg[2], arg[3]);
        }

        else
        {
            printf("Somethings broken\n");
        }

        // NOW WE CAN CALL FORK AND DO THE REST!

        // int pidd = fork();

        // if (pidd == 0){ // if its the child

        //     int size = sizeof(arg);

        // }
    }
}
