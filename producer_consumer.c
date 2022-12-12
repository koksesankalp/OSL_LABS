#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#define MaxItems 2 // maximum items a producer can produce or a consumer can consume
#define BufferSize 2 // size of the buffer

sem_t empty;
sem_t full;
int in = 0;//index at which producer will put the next data
int out = 0;// index from which the consumer will consume next data
int buffer[BufferSize];
pthread_mutex_t mutex;

void *producer(void *pno)
{   
    int item;
    for(int i = 0; i < MaxItems; i++) {
        item = rand(); // Produce an random item
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);//wait() operation to reduce the value by 1
        buffer[in] = item;
        printf("Producer %d: Insert Item %d at %d\n", *((int *)pno),buffer[in],in);
        in = (in+1)%BufferSize;
        
        pthread_mutex_unlock(&mutex);//signal() operation
        sem_post(&full);//signal() operation
    }
}
void *consumer(void *cno)
{   
    for(int i = 0; i < MaxItems; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);//same aswait() operation
        int item = buffer[out];
        printf("Consumer %d: Remove Item %d from %d\n",*((int *)cno),item, out);
        out = (out+1)%BufferSize;
        pthread_mutex_unlock(&mutex);//signal() operation
        sem_post(&empty);//this is the signal() operation to increment the value by 1
    }
}

int main()
{   
//two producers and consumers
    pthread_t pro[2],con[2];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,BufferSize);
    sem_init(&full,0,0);

    int a[2] = {1,2}; //just used for numbering the producer and consumer

    for(int i = 0; i < 2; i++) {
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
    }
    for(int i = 0; i < 2; i++) {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
    }

    for(int i = 0; i < 2; i++) {
        pthread_join(pro[i], NULL);
    }
    for(int i = 0; i < 2; i++) {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex);//this is to destroy the mutex to avoid memory leakage
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
    
}