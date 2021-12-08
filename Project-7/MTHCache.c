#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "MTCache.h"

typedef struct _node {
    int id;
    // pthread_mutex_t *locker;
    struct _node *next;
    struct _node *prev;
} Node;

typedef struct _mt_cache {
    int size;
    pthread_mutex_t *locker;
    Node *mru;
} MTCache;

MTCache *MTL_init(int size) {
    MTCache *cache = malloc(sizeof(MTCache));
    cache->size = size;
    pthread_mutex_init(cache->locker, NULL);
    cache->mru = NULL;
    return cache;
}

int MTL_add(MTCache *cache, int value) {
    pthread_mutex_lock(cache->locker);
    if(cache->mru == NULL) {
        cache->mru = malloc(sizeof(Node));
        cache->mru->id = value;
    }
    Node *curr = cache->mru;
    pthread_mutex_unlock(cache->locker);
}

int MTL_update(MTCache *cache, int value) {

}

int MTL_delete(MTCache *cache, int value) {

}

int MTL_size(MTCache *cache) {

}

void MTH_print(MTCache *cache) {

}