#ifndef __WORKER_H__
#define __WORKER_H__

#include "queue_task.h"

// extern volatile int total_primes;
extern pthread_mutex_t prime_mutex;

typedef struct Worker {
    // int id; // for debug
    int *prime_counter;
    Queue_Task *queue;
} Worker;

bool isPrime(int n);
void* worker(void *arg);
// Worker* create_worker(int id, int *counter, Queue_Task *queue);
Worker* create_worker(int *counter, Queue_Task *queue);
void free_worker(Worker *worker);
int check_producers();

#endif

