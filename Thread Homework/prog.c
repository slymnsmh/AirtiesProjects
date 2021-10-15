#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 2

/* Global variables for threads to share */
int value = 80;
int runningThread = 1;
pthread_mutex_t lock;

void *runner(void *id)
{
    printf("%d - %ld - %d - %d\n", runningThread, pthread_self(), (*(int*)id), value);
    while (value < 100) {
        pthread_mutex_lock(&lock);
        if (runningThread == (*(int*)id)) {
            value++;
            printf("Inside thread %d: id -> %ld, value -> %d\n", (*(int*)id), pthread_self(), value);
        }
        runningThread = NUM_THREADS - ((runningThread + 1) % NUM_THREADS);
        printf("--- %d ---\n", runningThread);
        pthread_mutex_unlock(&lock);
    }

    pthread_exit(0);
}

int main(int argc, char **argv)
{
	int i;

	pthread_t workers[NUM_THREADS];
    pthread_mutex_init(&lock, NULL);

	for (i = 0; i < NUM_THREADS; i++)
	{
		/* Now we will create the thread passing it data as a paramater*/
        int threadIndex = i + 1;
        pthread_create(&workers[i], NULL, runner, &threadIndex);
        printf("Thread %d is created. Id: %ld\n", threadIndex, workers[i]);
	}
	
	/* Waiting for threads to complete */
	for (i = 0; i < NUM_THREADS; i++)
	{
	    pthread_join(workers[i], NULL);
        printf("Thread %d is done.\n", i+1);
	}

    pthread_mutex_destroy(&lock);
    
	return 0;
}