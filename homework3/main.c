#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    srand(8);
    int random_array[1024][1024];
    int total_random[256];
    int num_threads = atoi(argv[1]);
    char *semname = "sema";
    sem_t  *my_sem;
    my_sem = sem_open(semname, O_CREAT, 777,1);
    

    for(int i = 0; i < 1024; i++){
        //printf("Printing from random_array: %d\n", random_array[i]);
        for(int j = 0; j < 1024; j++){
            random_array[i][j] = (rand()%256) + 1;
            // printf("Printing from random_array: %d\n", random_array[i][j]);
            // printf("Printing from total_random %d\n", total_random[i]);
        }
    }

    printf("Printing *semname: %s, and printing num_threads: %d ", semname, num_threads);




}