#include "worker.h"

pthread_mutex_t prime_mutex = PTHREAD_MUTEX_INITIALIZER;

// Function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

// Worker* create_worker(int id, int *counter, Queue_Task *queue){
Worker* create_worker(int *counter, Queue_Task *queue){
    Worker *worker = (Worker*)malloc(sizeof(Worker));
    if (worker == NULL) {
        fprintf(stderr, "Failed to allocate memory for worker\n");
        return NULL;
    }
    // worker->id = id;
    worker->prime_counter = counter;
    worker->queue = queue;
    return worker;
}

void free_worker(Worker *worker){
    if (worker == NULL) return;
    free(worker);
}

int check_producers(){
    for(int i = 0; i < NUM_PRODUCERS; i++){
        if(!producer_finished[i]){
            return 0;
        }
    }
    return 1;

}

void* worker(void *arg){
    // printf("enter to worker ");//debug
    Worker *worker = (Worker*)arg;
    // int id = worker->id;
    // printf("worker id: %d\n", id);//debug
    Queue_Task *queue = worker->queue;
    int num_of_primes = 0;
    while(1){ // We are using busy waiting for save time
        Task *task = NULL;
        pthread_mutex_lock(&queue_mutex);
        while((task = dequeue_task(queue)) == NULL){
            pthread_mutex_lock(&producer_mutex);
            // if(queue->size == 0 && producer_finished){
            if(queue->size == 0 && check_producers()){
                // printf("worker: %d, entered to goto condition\n", id);//debug
                goto end;
            }
            // if(!producer_finished){
            if(!check_producers()){
                pthread_mutex_unlock(&producer_mutex);
            }
            pthread_cond_wait(&queue_cond, &queue_mutex);
        }
        pthread_mutex_unlock(&queue_mutex);

            for(int i = 0; i < task->size; i++){
                if(isPrime(task->array[i])){
                    num_of_primes++;
                }
            }
            (*worker->prime_counter) += num_of_primes;
            num_of_primes = 0;
            free_task(task);   
    }
    end: 
        // printf("enter to end\n");//debug
        pthread_mutex_unlock(&producer_mutex);
        pthread_mutex_unlock(&queue_mutex);      
        // printf("worker %d terminating\n", id); // debug
        free_worker(worker);
        return NULL;
}