#ifndef __TASK_H__
#define __TASK_H__

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <semaphore.h>

// #define BUFFER_SIZE 10
#define BUFFER_SIZE 1000
#define NUM_THREADS 5
#define NUM_PRODUCERS 2 

extern int prime_counters[NUM_THREADS]; 

// extern bool producer_finished; 
extern bool producer_finished[NUM_PRODUCERS]; 
extern pthread_mutex_t producer_mutex;
extern pthread_cond_t producer_cond;


/// Task struct
typedef struct Task {
    int *array;
    int size;
    struct Task* next;
} Task;

Task* create_task(int *buffer, int size);
void free_task(Task* task);
void print_task_buffer(int *buff, int size);


#endif