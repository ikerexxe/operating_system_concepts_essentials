/*
 * Exercise 5.41 on page 257
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_RESOURCES   5
#define MAX_THREADS     5

int available_resources = MAX_RESOURCES;
pthread_mutex_t mutex;

/* decrease available resources by count resources */
/* return 0 if sufficient resources available, */
/* otherwise return -1 */
int decrease_count(int count) {
    int res;
    
    pthread_mutex_lock(&mutex);
    
    if (available_resources < count)
        res = -1;
    else {
        available_resources -= count;
        res = 0;
    }
    
    pthread_mutex_unlock(&mutex);
    return res;
}

/* increase available resources by count */
int increase_count(int count) {
    pthread_mutex_lock(&mutex);
    available_resources += count;
    pthread_mutex_unlock(&mutex);
}

void* do_something(void* arg) {
    int period = rand() % MAX_THREADS;
    int resources = (rand() % MAX_RESOURCES) + 1;
    
    printf("period %d\n", period);
    
    sleep(period);
    printf("decrease counter by %d\n", resources);
    decrease_count(resources);
    sleep(period);
    printf("increase counter by %d\n", resources);
    increase_count(resources);
    
    return NULL;
}

int main()
{
    int i = 0;
    int error;
    pthread_t workers[MAX_THREADS];
    
    if (pthread_mutex_init(&mutex, NULL) != 0) { 
        printf("Mutex init has failed\n"); 
        return 1; 
    } 
    
    for (int i = 0; i < MAX_THREADS; i++) {
        error = pthread_create(&(workers[i]), NULL, &do_something, NULL);
        if (error != 0) {
            printf("Thread can't be created : [%s]", strerror(error));
        }
    }
    
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(workers[i], NULL);
    }
    
    pthread_mutex_destroy(&mutex);
    
    printf("Finished\n"); 

    return 0;
}
