#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>

int random_array[1024][1024];
int total_random[256];

typedef struct
{
    int start;
    int end;
} partition_info;

void *thread_func(void *arg)
{
    partition_info *partition = (partition_info *)arg;
    int start = partition->start;
    int end = partition->end;
    int my_array[256];

    for (int i = start; i < end; i++)
    {
        for (int j = 0; j < 1024; j++)
        {
            int num = random_array[i][j];
            my_array[num] += 1;
        }
    }
    for (int i = 0; i < 256; i++)
    {
        total_random[i] += my_array[i];
    }

    return NULL;
}
int main(int argc, char *argv[])
{
    srand(8);
    int num_threads = atoi(argv[1]);
    char *semname = "sema";
    // int partition_size = num_threads;

    sem_t *my_sem;
    my_sem = sem_open(semname, O_CREAT, 777, 1);
    pthread_t tids[num_threads];
    partition_info partitions[num_threads];

    for (int i = 0; i < 1024; i++)
    { // filling out random_array with random integers from 0 to 256
        for (int j = 0; j < 1024; j++)
        {
            random_array[i][j] = (rand() % 256);
        }
    }

    for (int i = 0; i < num_threads; i++)
    { // Creating threads
        partitions[i].start = i * num_threads;
        partitions[i].end = (i + 1) * num_threads;

        pthread_create(&tids[i], NULL, thread_func, &partitions[i]);
    }

    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(tids[i], NULL);
    }

    // for (int x = 0; x < 10; x++){
    //     for(int y = 0; y < 10; y++){
    //         printf("From random_array: %d\n", random_array[x][y]);
    //     }
    // }

    printf("Printing *semname: %s, and printing num_threads: %d \n", semname, num_threads);
    for (int i = 0; i < 256; i++)
    {
        printf("Printing total number of %d's my total_random: %d\n", i, total_random[i]);
    }
}