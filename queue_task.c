#include "queue_task.h"

pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t queue_cond = PTHREAD_COND_INITIALIZER;

void print_queue(Queue_Task *queue)
{
    if (queue == NULL)
    {
        return;
    }
    Task *temp = queue->front;
    while (temp != NULL)
    {
        for (int i = 0; i < temp->size; i++)
        {
            printf("%d ", temp->array[i]);
        }
        temp = temp->next;
    }

}

// Function to create a new queue
Queue_Task* create_Queue() {
    Queue_Task *queue = (Queue_Task*)malloc(sizeof(Queue_Task));
    if (queue == NULL) {
        fprintf(stderr, "Failed to allocate memory for queue\n");
        return NULL;
    }
    queue->size = 0;
    queue->front = queue->rear = NULL;
    
    return queue;
}

// Function to destroy the queue
void destroy_Queue(Queue_Task *queue) {
    if (queue == NULL) return;

    // Dequeue all tasks
    while (queue->front != NULL) {
        Task *temp = queue->front;
        queue->front = queue->front->next;
        free_task(temp);
    }
    // Destroy the mutex
    pthread_mutex_destroy(&queue_mutex);

    // Destroy the condition variable
    pthread_cond_destroy(&queue_cond);

    // Free the queue structure
    free(queue);
}

// Function to submit a task to the queue
void submit_task(Queue_Task *queue, Task *task) {
    if (queue == NULL || task == NULL) return;

    // pthread_mutex_lock(queue->queue_mutex);
    pthread_mutex_lock(&queue_mutex);

    if (queue->rear == NULL) {
        // If the queue is empty, new task is both the front and rear
        queue->front = queue->rear = task;
    } else {
        // Add the new task at the end of the queue and change rear
        queue->rear->next = task;
        queue->rear = task;
    }
    queue->size++;
    // printf("enqueue - queue size: %d\n", queue->size); // debug
    // pthread_cond_broadcast(queue->queue_cond);
    // pthread_mutex_unlock(queue->queue_mutex);
    pthread_cond_broadcast(&queue_cond);
    pthread_mutex_unlock(&queue_mutex);
}


// Function to dequeue a task from the queue
Task* dequeue_task(Queue_Task *queue) {
    if (queue == NULL) return NULL;

    // pthread_mutex_lock(queue->queue_mutex);
    // pthread_mutex_lock(&queue_mutex);

    if (queue->front == NULL) {
        // If the queue is empty, return NULL
        // pthread_mutex_unlock(&queue_mutex);
        return NULL;
    }

    // Store the previous front and move front one node ahead
    Task *temp = queue->front;
    queue->front = queue->front->next;

    // If the front becomes NULL, then change rear to NULL
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    queue->size--;
    // printf("dequeue - queue size: %d\n", queue->size); // debug
    // pthread_mutex_unlock(&queue_mutex);
    return temp;
}