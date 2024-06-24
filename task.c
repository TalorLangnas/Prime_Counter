#include "task.h"

// Function to create a new task
// Task* create_task(int *buffer, int size, int *result) {
Task* create_task(int *buffer, int size) {
    // Allocate memory for the new task
    Task* new_task = (Task*)malloc(sizeof(Task));
    if (new_task == NULL) {
        fprintf(stderr, "Failed to allocate memory for task\n");
        return NULL;
    }   

    // Allocate memory for the deep copy of the array
    new_task->array = (int*)malloc(size * sizeof(int));
    if (new_task->array == NULL) {
        fprintf(stderr, "Failed to allocate memory for task array\n");
        free(new_task);
        return NULL;
    }

    memcpy(new_task->array, buffer, size * sizeof(int));
        
    // Set the task attributes
    new_task->size = size;
    new_task->next = NULL;

    return new_task;
}

// Function to free a task
void free_task(Task* task) {
    if (task != NULL) {
        if (task->array != NULL) {
            free(task->array); // Free the array allocated within the task
        }
        // Do not destroy the mutex here because it is not owned by the task
        free(task); // Free the task itself
    }
}

void print_task_buffer(int *buff, int size){
    // print the buffer
    int i = 0;
    printf("[%d, ", buff[i]);
    i++;
    while (i < size - 1) {
        printf("%d, ", buff[i]);
        i++;
    }
    printf("%d]\n", buff[i]);
}