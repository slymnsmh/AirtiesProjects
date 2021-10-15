#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_OF_THREADS 2

int value;

void *threadFunc(void* info) {
    sleep(1);
    printf("Inside thread %d:\n", *((int*)info));
    if (value >= 100) {
        pthread_exit(NULL);
    }
    value++;
    printf("Thread with id %ls incremented value by 1. New value: %d\n", (int *)info, value);
    return NULL;
}

int main() {
    FILE *filePtr = fopen("file.txt", "r");

    if (filePtr == NULL) {
        printf("Cannot open file!");
        exit(-1);
    }

    fscanf(filePtr, "%d", &value);
    printf("Before any incremention, the value is: %d\n", value);

    pthread_t threadIds[NUM_OF_THREADS];
    
    int i;
    for (i = 0; i < NUM_OF_THREADS; i++) {
        pthread_create(&threadIds[i], NULL, threadFunc, &i);
        printf("Thread %d is created.\n", i);
    }

    /*i = 0;
    while (value <= 100) {
        sleep(1);
        printf("---Value %d: Wait for 1. Itertion: %d\n", value, i);
        pthread_join(threadIds[0], NULL);
        printf("------Value %d: Wait for 1. Itertion: %d\n", value, i);
        pthread_join(threadIds[1], NULL);
    }*/

    pthread_join(threadIds[0], NULL);
    pthread_join(threadIds[1], NULL);
    pthread_exit(NULL);
    return 0;
}