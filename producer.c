#include "producer.h"


// Producer* create_producer(int *buffer, int *buff_index, Queue_Task *queue){
Producer* create_producer(int *buffer, int *buff_index, bool *flag, Queue_Task *queue){
    Producer *producer = (Producer *)malloc(sizeof(Producer));
    producer->buffer = buffer;
    producer->buff_index = buff_index;
    producer->queue = queue;
    producer->producer_finished = flag;
    return producer;
}

void free_producer(Producer *producer){
    if (producer == NULL) return;
    if(!producer->buffer){
        free(producer->buffer);    
    }
    free(producer);
}

void* producer(void *arg) {
    Producer *producer = (Producer *)arg;
    int *buffer = producer->buffer;
    int *buff_index = producer->buff_index;
    Queue_Task *queue = producer->queue;

    while (1) {
        // Read data to the buffer until it is full
        while (*buff_index < BUFFER_SIZE) {
            if (scanf("%d", &buffer[*buff_index]) == EOF) {
                if (feof(stdin)) {
                    // EOF reached, break the loop
                    pthread_mutex_lock(&producer_mutex);
                    // producer_finished = true;
                    (*producer->producer_finished) = true;
                    pthread_mutex_unlock(&producer_mutex);
                    break;
                } else if (ferror(stdin)) {
                    // scanf failed due to an error
                    perror("scanf");
                    pthread_mutex_lock(&producer_mutex);
                    // producer_finished = true;
                    (*producer->producer_finished) = true;
                    pthread_mutex_unlock(&producer_mutex);
                    break;
                }
            }
            // printf("Read %d: %d\n", *buff_index, buffer[*buff_index]);
            (*buff_index)++;
        }

        // If generation is finished, break the outer loop
        pthread_mutex_lock(&producer_mutex);
        // if (producer_finished) {
        if ((*producer->producer_finished)) {
            // printf("entered to producer_finished\n"); // debug
            if(*buff_index > 0){
                // printf("buff_index: %d\n", *buff_index); // debug
                Task *task = create_task(buffer, *buff_index);
                *buff_index = 0;
                submit_task(queue, task);
            }
            pthread_mutex_unlock(&producer_mutex);
            break;
        }
        pthread_mutex_unlock(&producer_mutex);
        // printf("buff_index: %d\n", *buff_index); // debug
        // Generate task from the buffer
        Task *task = create_task(buffer, *buff_index);
        *buff_index = 0;

        // Add the task to the queue
        submit_task(queue, task);
    }
    free_producer(producer);

    return NULL;    
}