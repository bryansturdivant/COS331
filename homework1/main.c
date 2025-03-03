#include <stdio.h> // I have to get better at knowing what I actually need as an include 
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    char buffer[100];
    while (1)
    {
        printf("Enter the program name\n");
        int ret = read(0, buffer, 100);
        buffer[ret - 1] = '\0';

        int pidd = fork();

        if (pidd == 0)
        { // if its the child?

            printf("Program name: %s\n", buffer);
            char *arg[] = {buffer, NULL}; // Sets up the vector array?

            execv(buffer, arg);
            printf("If I'm still here then there is a problem!\n");
            exit(1); // Terminates the CURRENT child - not the entire program
        }
        else
        {
            wait(0);
        }
    }


}

