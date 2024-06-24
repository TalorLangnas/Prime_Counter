#ifndef __QUEUE_TASK_H__
#define __QUEUE_TASK_H__
#include "task.h"

extern pthread_mutex_t queue_mutex;
extern pthread_cond_t queue_cond;


// Queue struct for tasks
typedef struct Queue_Task {
    Task *front, *rear;
    int size;
} Queue_Task;

Queue_Task* create_Queue();
void destroy_Queue(Queue_Task *queue);
void submit_task(Queue_Task *queue, Task *task);
Task* dequeue_task(Queue_Task *queue);
void print_queue(Queue_Task *queue);


#endif