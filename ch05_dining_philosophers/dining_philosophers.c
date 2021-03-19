/*
 * Programming project on page 260
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_THREADS     5
#define MAX_SLEEP_TIME  3

int forks[MAX_THREADS];
pthread_mutex_t mutex;
pthread_cond_t condition[MAX_THREADS];

int pickup_forks(int id) {
    int res;
    
    pthread_mutex_lock(&mutex);
    while(!forks[id] || !forks[((id + 1) % MAX_THREADS)]) {
        if(!forks[id]) {
            printf("philosopher %d: waits for fork %d\n", id, id);
            pthread_cond_wait(&condition[id], &mutex);
        } else {
            printf("philosopher %d: waits for fork %d\n", id, ((id + 1) % MAX_THREADS));
            pthread_cond_wait(&condition[((id + 1) % MAX_THREADS)], &mutex);
        }
    }
    printf("philosopher %d: picks up forks %d and %d\n", id, id, ((id + 1) % MAX_THREADS));
    forks[id] = 0;
    forks[(id + 1) % MAX_THREADS] = 0;
    
    
    return res;
}

int return_forks(int id) {
    printf("philosopher %d: returns forks %d and %d\n", id, id, ((id + 1) % MAX_THREADS));
    forks[id] = 1;
    forks[((id + 1) % MAX_THREADS)] = 1;
    pthread_cond_signal(&condition[id]);
    pthread_cond_signal(&condition[((id + 1) % MAX_THREADS)]);
    pthread_mutex_unlock(&mutex);
}

void think(int period) {
    sleep(period);
}

void eat(int id, int period) {
    pickup_forks(id);
    sleep(period);
    return_forks(id);
}

void* have_dinner(void* arg) {
    int id = *((int *) arg);
    int period = (rand() % MAX_SLEEP_TIME) + 1;
    
    printf("period %d\n", period);
    
    for(int i = 0; i < MAX_THREADS; i++) {
        think(period);
        eat(id, period);
    }
    
    return NULL;
}

int main()
{
    int i = 0;
    int error;
    pthread_t philosopher[MAX_THREADS];
    
    if (pthread_mutex_init(&mutex, NULL) != 0) { 
        printf("Mutex init has failed\n"); 
        return 1; 
    }
    
    for (int i = 0; i < MAX_THREADS; i++) {
        forks[i] = 1;
        if (pthread_cond_init(&condition[i], NULL) != 0) { 
            printf("Condition init has failed\n"); 
            return 1; 
        }
    }
    
    for (int i = 0; i < MAX_THREADS; i++) {
        int *arg = malloc(sizeof(*arg));
        *arg = i;
        error = pthread_create(&(philosopher[i]), NULL, &have_dinner, arg);
        if (error != 0) {
            printf("Thread can't be created : [%s]", strerror(error));
        }
    }
    
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(philosopher[i], NULL);
    }
    
    pthread_mutex_destroy(&mutex);
    
    printf("Finished\n"); 

    return 0;
}
