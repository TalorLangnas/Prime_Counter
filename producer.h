#ifndef __PRODUCER_H__
#define __PRODUCER_H__
#include "queue_task.h"


typedef struct Producer {
    int *buffer;
    int *buff_index;
    bool *producer_finished;
    Queue_Task *queue;
} Producer;

void* producer(void *arg);
// Producer* create_producer(int *buffer, int *buff_index, Queue_Task *queue);
Producer* create_producer(int *buffer, int *buff_index, bool *flag, Queue_Task *queue);
void free_producer(Producer *producer);


#endif