/*
** Name: Elizabeth Perez
** Student ID: eperez57
** M-number: M20966722
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "MTCounter.h"

typedef struct _mt_counter {
    int count;
    pthread_mutex_t *locker;
} MTCounter;

MTCounter *MTC_init() {
    MTCounter *counter = malloc(sizeof(MTCounter));
    if(counter == NULL) return NULL; /* Malloc Error */
    counter->count = 0;
    pthread_mutex_init(counter->locker, NULL);
    return counter;
}

int MTC_value(MTCounter *counter) {
    pthread_mutex_lock(counter->locker);
    int value = counter->count;
    pthread_mutex_unlock(counter->locker);
    return value;
}

void MTC_increment(MTCounter *counter) {
    pthread_mutex_lock(counter->locker);
    counter->count++;
    pthread_mutex_unlock(counter->locker);
}

void MTC_decrement(MTCounter *counter) {
    pthread_mutex_lock(counter->locker);
    counter->count--;
    pthread_mutex_unlock(counter->locker);
}

int MTC_destroy(MTCounter *counter) {
    int value = MTC_value(counter);
    pthread_mutex_destroy(counter->locker);
    free(counter);
    return value;
}