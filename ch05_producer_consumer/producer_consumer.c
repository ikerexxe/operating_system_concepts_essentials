/*
 * Programming project on page 262
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define BUFFER_SIZE     5
#define SEM_SIZE        3
#define MAX_SLEEP_TIME  3

pthread_mutex_t mutex;
sem_t empty, full;

typedef int buffer_item;
buffer_item buffer[BUFFER_SIZE];
int buffer_count = 0;

int insert_item(int id, buffer_item item) {
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    
    if (buffer_count == BUFFER_SIZE) {
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        return -1;
    }
    
    buffer_count++;
    buffer[buffer_count] = item;
    printf("Producer %d produced %d\n", id, item);
    
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
    
    return 0;
}

int remove_item(int id, buffer_item *item) {
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    
    if (buffer_count == 0) {
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        return -1;
    }
    
    (*item) = buffer[buffer_count];
    buffer_count--;
    printf("Consumer %d consumed %d\n", id, *item);
    
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
    
    return 0;
}

void *producer(void *arg) {
    int id = *((int *) arg);
    buffer_item item;
    int sleep_time = (rand() % MAX_SLEEP_TIME) + 1;
    
    while (1) {
        sleep(sleep_time);
        /* generate a random number */
        item = rand();
        if (insert_item(id, item)) {
            printf("Error: producer %d buffer full\n", id);
        }
    }
}

void *consumer(void *arg) {
    int id = *((int *) arg);
    buffer_item item;
    int sleep_time = (rand() % MAX_SLEEP_TIME) + 1;
    
    while (1) {
        sleep(sleep_time);
        if (remove_item(id, &item)) {
            printf("Error: consumer %d buffer empty\n", id);
        }
    }
}

int main()
{
    int error;
    int sleep_time = 10;
    int num_producers = 5;
    int num_consumers = 5;
    pthread_t producer_threads[num_producers];
    pthread_t consumer_threads[num_consumers];
    
    for (int i = 0; i <= BUFFER_SIZE; i++) {
        buffer[i] = 0;
    }
    
    if (pthread_mutex_init(&mutex, NULL) != 0) { 
        printf("Mutex init has failed\n"); 
        return 1; 
    }
    
    if (sem_init(&empty, 0, SEM_SIZE) != 0) {
        printf("empty semaphore init has failed\n"); 
        return 1; 
    }
    
    if (sem_init(&full, 0, SEM_SIZE) != 0) {
        printf("full semaphore init has failed\n"); 
        return 1; 
    }
    
    for (int i = 0; i < num_producers; i++) {
        int *arg = malloc(sizeof(*arg));
        *arg = i;
        error = pthread_create(&(producer_threads[i]), NULL, &producer, arg);
        if (error != 0) {
            printf("Producer can't be created : [%s]", strerror(error));
        }
    }
    
    for (int i = 0; i < num_consumers; i++) {
        int *arg = malloc(sizeof(*arg));
        *arg = i;
        error = pthread_create(&(consumer_threads[i]), NULL, &consumer, arg);
        if (error != 0) {
            printf("Consumer can't be created : [%s]", strerror(error));
        }
    }
    
    sleep(sleep_time);
    
    sem_destroy(&full);
    sem_destroy(&empty);
    pthread_mutex_destroy(&mutex);
    
    printf("Finished\n"); 

    return 0;
}
