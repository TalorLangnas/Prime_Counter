#include "producer.h"


Producer* create_producer(bool *flag, Queue_Task *queue){
    // int *buffer = NULL;
    Producer *producer = (Producer *)malloc(sizeof(Producer));
    if (!(producer->buffer = (int *)malloc(BUFFER_SIZE * sizeof(int)))) {
        fprintf(stderr, "Failed to allocate memory\n");
        return NULL;
    };
    producer->queue = queue;
    producer->producer_finished = flag;
    return producer;
}

void free_producer(Producer *producer){
    if (producer == NULL) return;
    if(producer->buffer){
        free(producer->buffer);    
    }
    free(producer);
}

void* producer(void *arg) {
    Producer *producer = (Producer *)arg;
    int *buffer = producer->buffer;
    int curr_buff_size = 0;
    Queue_Task *queue = producer->queue;

    while (1) {
        // Read data to the buffer 
        while (curr_buff_size < BUFFER_SIZE) {
            if (scanf("%d", &buffer[curr_buff_size]) == EOF) {
                if (feof(stdin)) {
                    // EOF reached, break the loop
                    pthread_mutex_lock(&producer_mutex);
                    (*producer->producer_finished) = true;
                    pthread_mutex_unlock(&producer_mutex);
                    break;
                } else if (ferror(stdin)) {
                    // scanf failed due to an error
                    perror("scanf");
                    pthread_mutex_lock(&producer_mutex);
                    (*producer->producer_finished) = true;
                    pthread_mutex_unlock(&producer_mutex);
                    break;
                }
            }
            curr_buff_size++;
        }

        // If generation is finished, break the outer loop
        pthread_mutex_lock(&producer_mutex);
        if ((*producer->producer_finished)) {
            if(curr_buff_size > 0){
                Task *task = create_task(buffer, curr_buff_size);
                curr_buff_size = 0;
                submit_task(queue, task);
            }
            pthread_mutex_unlock(&producer_mutex);
            break;
        }
        pthread_mutex_unlock(&producer_mutex);
        Task *task = create_task(buffer, curr_buff_size);
        curr_buff_size = 0;        

        // Add the task to the queue
        submit_task(queue, task);
    }
    free_producer(producer);

    return NULL;    
}