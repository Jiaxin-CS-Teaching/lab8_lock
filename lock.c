/*
This program provides a possible solution for producer-consumer problem using mutex and semaphore.
*/
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#define MaxItems 5 // Num of items a producer/consumer can produce/consume
#define BufferSize 5 // Size of the buffer

pthread_mutex_t mutex;
sem_t empty;
sem_t full;

int in = 0;
int out = 0;
int buffer[BufferSize];

void *producer(void *pno)
{   
    int item;

    for(int i = 0; i < MaxItems; i++)
    {
        item = rand() % 10; // Produce a random item
/************* Critical Secion ***********/
        buffer[in] = item;
        printf("Producer %d: Insert Item %d at slot %d\n", *((int *)pno), buffer[in], in);
        in = (in + 1) % BufferSize;
/************* End ***********/
    }
}

void *consumer(void *cno)
{
    int item;

    for(int i = 0; i < MaxItems; i++)
    {
/************* Critical Secion ***********/
        item = buffer[out];
        printf("Consumer %d: Remove Item %d from slot %d\n",*((int *)cno), item, out);
        out = (out + 1) % BufferSize;
/************* End ***********/
    }
}

int main()
{
    pthread_t pro[5], con[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BufferSize);
    sem_init(&full, 0, 0);

    int a[5] = {1, 2, 3, 4, 5}; //Numbering the producer and consumer

    for(int i = 0; i < 5; i++)
    {
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
    }
    for(int i = 0; i < 5; i++)
    {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
    }

    for(int i = 0; i < 5; i++)
    {
        pthread_join(pro[i], NULL);
    }

    for(int i = 0; i < 5; i++)
    {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
    
}