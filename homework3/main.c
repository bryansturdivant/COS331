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
char *sems[256][10];

int total = 0;
char *semname = "sema"; //!!!This was in main, maybe put it back if this doesn't work!!!
sem_t *my_sem;          // declaring my_sem semaphore
sem_t *my_sems[256];    // declaring my_sems[256] for an array of semaphores

typedef struct
{
    int id;
    int start;
    int end;
    int threads;
} partition_info;

void *thread_func1(void *arg)
{

    partition_info *partition = (partition_info *)arg;
    // int chunk = 1024/partition->threads;
    int start = partition->start;
    int end = partition->end;
    int my_array[256] = {0};
    int id = partition->id;
    // pthread_t tid = pthread_self();

    for (int i = start; i < end; i++)
    {
        for (int j = 0; j < 1024; j++)
        {
            int num = random_array[i][j];
            my_array[num] += 1;
            total += 1;
            // printf("Total numbers from total with no Semaphore: %d\n", total);
        }
    }
    for (int i = 0; i < 256; i++)
    {
        total_random[i] += my_array[i];
    }
    printf("From Func1: Work done by thread #: %d\nTotal so far is: %d\n", id, total);

    return NULL;
}

void *thread_func2(void *arg)
{
    sem_wait(my_sem);
    partition_info *partition = (partition_info *)arg;
    // int chunk = 1024/partition->threads;
    int start = partition->start;
    int end = partition->end;
    int my_array[256] = {0};
    int id = partition->id;
    // pthread_t tid = pthread_self();

    for (int i = start; i < end; i++)
    {
        for (int j = 0; j < 1024; j++)
        {
            int num = random_array[i][j];
            my_array[num] += 1;
            total += 1;
            // printf("Total numbers from total with 1 Semaphore: %d\n", total);
        }
    }
    for (int i = 0; i < 256; i++)
    {
        total_random[i] += my_array[i];
    }
    printf("From func2: Work done by thread #: %d\nTotal so far: %d\n", id, total);

    sem_post(my_sem);

    return NULL;
}

void *thread_func3(void *arg)
{

    // sem_wait(my_sems[i]); //
    partition_info *partition = (partition_info *)arg;
    // int chunk = 1024/partition->threads;
    int start = partition->start;
    int end = partition->end;
    int my_array[256] = {0};
    int id = partition->id;
    // pthread_t tid = pthread_self();

    for (int i = start; i < end; i++)
    {
        for (int j = 0; j < 1024; j++)
        {
            int num = random_array[i][j];
            my_array[num] += 1;
            total += 1;
            // printf("Total numbers from total with 1 Semaphore: %d\n", total);
        }
    }
    for (int i = 0; i < 256; i++)
    {
        sem_wait(my_sems[i]);
        total_random[i] += my_array[i];
        sem_post(my_sems[i]);
    }
    printf("From func3: Work done by thread #: %d\nTotal so far: %d\n", id, total);

    // sem_post(my_sems[i]);
    return NULL;
}

int main(int argc, char *argv[])
{
    srand(8);
    int num_threads = atoi(argv[1]);
    int chunk = 1024 / num_threads;

    my_sem = sem_open(semname, O_CREAT, 777, 1); // single semaphore - might want change this?
    pthread_t tids[num_threads];
    partition_info partitions[num_threads];

    for (int i = 0; i < 256; i++)
    { // instantiate my array of semaphores
        sprintf(sems[i], "S%d", i);
        my_sems[i] = sem_open(sems[i], O_CREAT, 777, 1);
    }

    for (int i = 0; i < 1024; i++)
    { // filling out random_array with random integers from 0 to 256
        for (int j = 0; j < 1024; j++)
        {
            random_array[i][j] = (rand() % 256);
        }
    }

    for (int i = 0; i < num_threads; i++) // Creating threads for first function - no semaphores
    {                                     // Creating threads
        partitions[i].id = i;
        partitions[i].start = (i * chunk);
        partitions[i].end = (partitions[i].start + chunk);
        printf("Thread has id: %d with a start: %d and end: %d\n", partitions[i].id, partitions[i].start, partitions[i].end);

        pthread_create(&tids[i], NULL, thread_func1, &partitions[i]);
    }

    for (int i = 0; i < num_threads; i++) // joining threads for first function
    {
        pthread_join(tids[i], NULL);
    }

    total = 0; // reset total for the next thread function

    for (int i = 0; i < num_threads; i++) // Creating threads for second function - 1 semaphore
    {                                     // Creating threads
        partitions[i].id = i;
        partitions[i].start = (i * chunk);
        partitions[i].end = partitions[i].start + chunk;
        printf("Second function Thread has id: %d with a start: %d and end: %d\n", partitions[i].id, partitions[i].start, partitions[i].end);
        pthread_create(&tids[i], NULL, thread_func2, &partitions[i]);
    }

    for (int i = 0; i < num_threads; i++) // Joining threads for second function
    {
        pthread_join(tids[i], NULL);
    }
    total = 0; // reset total for the next thread function

    sem_close(my_sem); // Closing and unlinking single semaphore
    sem_unlink(semname);
    for (int i = 0; i < num_threads; i++) // Creating threads for third function - 256 semaphores
    {                                     // Creating threads
        partitions[i].id = i;
        partitions[i].start = (i * chunk);
        partitions[i].end = partitions[i].start + chunk;
        printf("Third function Thread has id: %d with a start: %d and end: %d\n", partitions[i].id, partitions[i].start, partitions[i].end);
        pthread_create(&tids[i], NULL, thread_func3, &partitions[i]);
    }

    for (int i = 0; i < num_threads; i++) // Joining threads for third function
    {
        pthread_join(tids[i], NULL);
    }

    for (int i = 0; i < 256; i++)
    { // closing and unlinking my array of semaphores
        sem_close(my_sems[i]);
        sem_unlink(sems[i]);
    }

    // for (int x = 0; x < 10; x++){
    //     for(int y = 0; y < 10; y++){
    //         printf("From random_array: %d\n", random_array[x][y]);
    //     }
    // }

    // printf("Printing *semname: %s, and printing num_threads: %d \n", semname, num_threads);
    // for (int i = 0; i < 256; i++)
    // {
    //     printf("Printing total number of %d's from my total_random: %d\n", i, total_random[i]);
    //     printf("Printing total numbers from total: %d\n", total);
    // }
}