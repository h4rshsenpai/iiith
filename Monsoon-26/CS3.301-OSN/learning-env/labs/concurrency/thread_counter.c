#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define THREADS 4
#define INCREMENTS 100000

static long counter = 0;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

static void *worker(void *arg) {
    long id = *(long *)arg;

    for (int i = 0; i < INCREMENTS; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }

    printf("thread %ld finished\n", id);
    return NULL;
}

int main(void) {
    pthread_t threads[THREADS];
    long ids[THREADS];

    for (long i = 0; i < THREADS; i++) {
        ids[i] = i;
        if (pthread_create(&threads[i], NULL, worker, &ids[i]) != 0) {
            perror("pthread_create");
            return 1;
        }
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("expected=%d actual=%ld\n", THREADS * INCREMENTS, counter);
    return 0;
}
