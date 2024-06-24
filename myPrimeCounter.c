// #include "thread_pool.h"
#include "producer.h"
#include "worker.h"

Queue_Task *queue = NULL;
// bool producer_finished = false;
bool producer_finished[NUM_PRODUCERS] = {false};

pthread_mutex_t producer_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t producer_cond = PTHREAD_COND_INITIALIZER;

/*
TRIES FOR IMPROVE TIME:
    1. Use busy waiting instead of condition variable - doesnt work
    2. Use multiple producer threads 
*/

int main(int argc, char *argv[]) {
    // Initialize variables
    int total_primes = 0;
    int *buffer = NULL;
    int buff_index = 0;
    queue = create_Queue();
    // pthread_t producer_thread;
    pthread_t producer_thread[2];
    pthread_t worker_threads[NUM_THREADS];
    int prime_counters[NUM_THREADS] = {0};

    buffer = (int *)malloc(BUFFER_SIZE * sizeof(int));
    if (buffer == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return 1;
    }
    for(int i = 0; i < NUM_THREADS; i++) {
        // Worker *worker_args = create_worker(i, &prime_counters[i], queue);
        Worker *worker_args = create_worker(&prime_counters[i], queue);
        if(pthread_create(&worker_threads[i], NULL, worker, (void*) worker_args)){
            fprintf(stderr, "Error creating worker thread\n");
            free_worker(worker_args);
            return 1;
        }
    }

    // initalize the input for Producer
    // Producer *producer_args = create_producer(buffer, &buff_index, queue);
    
    // if(pthread_create(&producer_thread, NULL, producer, (void*) producer_args)){
    //     fprintf(stderr, "Error creating producer thread\n");
    //     free_producer(producer_args);
    //     return 1;
    // }
    for(int i = 0; i < NUM_PRODUCERS; i++) {
        Producer *producer_args = create_producer(buffer, &buff_index, &producer_finished[i], queue);
        if(pthread_create(&producer_thread[i], NULL, producer, (void*) producer_args)){
            fprintf(stderr, "Error creating producer thread\n");
            free_producer(producer_args);
            return 1;
        }
    }
    
    // pthread_join(producer_thread, NULL);
    for(int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producer_thread[i], NULL);
    }
    
    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_join(worker_threads[i], NULL);
    }
    
    destroy_Queue(queue);
    
    // printf("worker threads finished\n\n"); // debug       
    // Sum prime_counters
    for(int i = 0; i < NUM_THREADS; i++){ 
        // printf("prime_counters[%d]: %d\n", i, prime_counters[i]); // debug
        total_primes += prime_counters[i];
    }
    free(buffer);

    printf("%d total primes.\n", total_primes);
    return 0;
}
