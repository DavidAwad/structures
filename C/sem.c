#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 5

/* global thread exit control flag */
volatile uint32_t g_ExitFlag = 0;

/* global thread execution control semaphore */
sem_t g_Sem;

/* the thread function */
void *ThreadFunc(void *pContext){
    uint32_t tid = (uint32_t)pContext;

    /* main thread loop */
    while (g_ExitFlag == 0){
        /* wait for semaphore to be signalled */
        sem_wait(&g_Sem);
        printf("Thread %d running.\n", tid);
    }

    printf("Thread %d exiting.\n", tid);

    return NULL;
}

int main(int argc, char *argv[]){
    uint32_t i = 0;
    pthread_t th;

    /* suppress warnings */
    (void)argc;
    (void)argv;

    /* initialize the semaphore */
    sem_init(&g_Sem, 0, 0);

    /* create and detach several threads */
    for (i = 0; i < NUM_THREADS; ++i){
        pthread_create(&th, NULL, ThreadFunc, (void *)i);
        pthread_detach(th);
    }

    /* run each thread four times and exit */
    for (i = 0; i < (NUM_THREADS * 4); ++i){
        if (i == 15)
        {
            g_ExitFlag = 1;
        }

        /* release a thread to execute */
        sem_post(&g_Sem);      
    }

    return 0;
}
