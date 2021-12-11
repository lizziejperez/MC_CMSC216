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
    int used;
    pthread_mutex_t *locker;
    Node *mru;
} MTCache;

MTCache *MTL_init(int size) {
    MTCache *cache = malloc(sizeof(MTCache));
    cache->size = size;
    pthread_mutex_init(cache->locker, NULL);
    cache->mru = NULL;
    cache->used = 0;
    return cache;
}

int MTL_add(MTCache *cache, int value) {
    if(value <= 0) return -1; /* Case: Invalid value given */

    pthread_mutex_lock(cache->locker);
    if(cache->mru == NULL) { /* Case: First entry */
        cache->mru = malloc(sizeof(Node));
        cache->mru->id = value;
        cache->mru->next = NULL;
        cache->mru->prev = NULL;
        cache->used++;
        pthread_mutex_unlock(cache->locker);
        return 0;
    }

    if(cache->mru->id == value) { /* Case: Already the mru in cache */
        pthread_mutex_unlock(cache->locker);
        return 0;
    }
    
    Node *curr = cache->mru;
    while(curr->next != NULL) {
        if(curr->next->id == value) { /* Case: Already in cache */
            Node *rem = curr->next->next;
            curr->next->prev = NULL;
            curr->next->next = cache->mru;
            cache->mru->prev = curr->next;
            cache->mru = curr->next;
            curr->next = rem;
            pthread_mutex_unlock(cache->locker);
            return 0;
        }
        curr = curr->next;
    }

    if(cache->used < cache->size) { /* Case: Add in cache at mru (cache not full) */
        Node *mru = malloc(sizeof(Node));
        mru->id = value;
        mru->prev = NULL;
        mru->next = cache->mru;
        cache->mru->prev = mru;
        cache->mru = mru;
        cache->used++;
        pthread_mutex_unlock(cache->locker);
        return 0;
    }

    /* Case: Add in cache at mru (cache full) */
    int rtn = curr->id;
    Node *prev = curr->prev;
    free(curr);
    prev->next = NULL;
    pthread_mutex_unlock(cache->locker);
    return rtn;
}

int MTL_update(MTCache *cache, int value) {
    if(cache->mru == NULL) return -1; /* Case: Empty cache */
    if(cache->mru->id == value) return 0; /* Case: Already mru */

    pthread_mutex_lock(cache->locker);
    Node *curr = cache->mru;
    while(curr->next != NULL) {
        if(curr->next->id == value) { /* Case: Update value to be mru */
            Node *rem = curr->next->next;
            curr->next->prev = NULL;
            curr->next->next = cache->mru;
            cache->mru->prev = curr->next;
            cache->mru = curr->next;
            curr->next = rem;
            pthread_mutex_unlock(cache->locker);
            return 0;
        }
        curr = curr->next;
    }
    pthread_mutex_unlock(cache->locker);
    return -1; /* Case: Value not found in cache */
}

int MTL_delete(MTCache *cache, int value) {
    if(cache->mru == NULL) return -1; /* Case: Empty cache */

    pthread_mutex_lock(cache->locker);
    if(cache->mru->id == value) { /* Case: Delete the mru node */
        Node *rem = cache->mru->next;
        free(cache->mru);
        cache->mru = rem;
        cache->mru->prev = NULL;
        cache->used--;
        pthread_mutex_unlock(cache->locker);
        return 0;
    }

    Node *curr = cache->mru;
    while(curr->next != NULL) {
        if(curr->next->id == value) { /* Case: Delete "middle" or end node */
            /* TODO */
            cache->used--;
            pthread_mutex_unlock(cache->locker);
            return 0;
        }
    }
    pthread_mutex_unlock(cache->locker);
    return -1; /* Case: Value not found in cache */
}

int MTL_size(MTCache *cache) {
    return cache->used;
    /*
    int used = 0;
    Node *curr = cache->mru;
    while(curr->next != NULL) {
        count++;
        curr = curr->next;
    }
    return count:
    */
}

void MTH_print(MTCache *cache) {
    pthread_mutex_lock(cache->locker);
    Node *curr = cache->mru;
    while(curr != NULL) {
        printf("%d", curr->id);
        curr = curr->next;
        if(curr != NULL) printf(" ");
    }
    pthread_mutex_unlock(cache->locker);
    printf("\n");
    return 0;
}