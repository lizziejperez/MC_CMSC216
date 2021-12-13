/*
** Name: Elizabeth Perez
** Student ID: eperez57
** M-number: M20966722
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "MTCache.h"

typedef struct _node {
    int id;
    struct _node *next;
} Node;

typedef struct _mt_cache {
    int size;
    int used;
    pthread_mutex_t *locker;
    Node *mru;
} MTCache;

MTCache *MTL_init(int size) {
    MTCache *cache = malloc(sizeof(MTCache));
    if(cache == NULL) return NULL; /* Malloc Error */
    cache->size = size;
    cache->used = 0;
    pthread_mutex_init(cache->locker, NULL);
    cache->mru = NULL;

    while(cache->size < size) {
        if(cache->mru == NULL) { /* Case: First node in cache */
            cache->mru = malloc(sizeof(Node));
            if(cache->mru == NULL) { /* Malloc Error */
                free(cache);
                return NULL;
            }
            cache->mru->id = -1;
            cache->mru->next = NULL;
        } else {
            Node *ptr = cache->mru;
            while(ptr->next != NULL)
                ptr = ptr->next;
            ptr->next = malloc(sizeof(Node));
            if(ptr->next == NULL) { /* Malloc Error */
                ptr = cache->mru;
                while(ptr != NULL) {
                    Node *del = ptr;
                    ptr = ptr->next;
                    free(del);
                }
                free(cache);
                return NULL;
            }
            ptr->next->id = -1;
            ptr->next->next = NULL;
        }
        cache->size++;
    }

    return cache;
}

int MTL_add(MTCache *cache, int value) {
    if(value <= 0) return -1; /* Case: Invalid value given */

    if(!MTL_update(cache, value)) return 0; /* Case: Already in cache */

    pthread_mutex_lock(cache->locker);
    if(cache->mru->id == -1) { /* Case: First entry */
        cache->mru->id = value;
        cache->used++;
        pthread_mutex_unlock(cache->locker);
        return 0;
    }

    Node *ptr = cache->mru;
    while(ptr->next != NULL) {
        if(ptr->next->id == -1) { /* Case: Add in cache at mru (cache not full) */
            Node *newMRU = ptr->next;
            ptr->next = newMRU->next;
            newMRU->id = value;
            newMRU->next = cache->mru;
            cache->mru = newMRU;
            cache->used++;
            pthread_mutex_unlock(cache->locker);
            return 0;
        }
        if(ptr->next->next == NULL) { /* Case: Add in cache at mru (cache full) */
            int rtn = ptr->next->id;
            Node *newMRU = ptr->next;
            ptr->next = NULL;
            newMRU->id = value;
            newMRU->next = cache->mru;
            cache->mru = newMRU;
            pthread_mutex_unlock(cache->locker);
            return rtn;
        }
        ptr = ptr->next;
    }
}

int MTL_update(MTCache *cache, int value) {
    pthread_mutex_lock(cache->locker);
    if(cache->mru->id == value) { /* Case: Already mru */
        pthread_mutex_unlock(cache->locker);
        return 0;
    }

    Node *ptr = cache->mru;
    while(ptr->next != NULL) {
        if(ptr->next->id == -1) { /* Case: Value not found in cache */
            pthread_mutex_unlock(cache->locker);
            return -1;
        }
        if(ptr->next->id == value) { /* Case: Update value to be mru */
            Node *newMRU = ptr->next;
            ptr->next = newMRU->next;
            newMRU->next = cache->mru;
            cache->mru = newMRU;
            pthread_mutex_unlock(cache->locker);
            return 0;
        }
        ptr = ptr->next;
    }
    pthread_mutex_unlock(cache->locker);
    return -1;
}

int MTL_delete(MTCache *cache, int value) {
    pthread_mutex_lock(cache->locker);
    if(cache->mru->id == value) { /* Case: Delete the mru node */
        Node *ptr = cache->mru;
        while(ptr->next != NULL) {
            if(ptr->next->id == -1) break;
            ptr = ptr->next;
        }
        Node *del = cache->mru;
        cache->mru = cache->mru->next;
        del->id = -1;
        del->next = ptr->next;
        ptr->next = del;
        cache->used--;
        pthread_mutex_unlock(cache->locker);
        return 0;
    }

    Node *parent = NULL;
    Node *ptr = cache->mru;
    while(ptr->next != NULL) {
        if(ptr->next->id == -1) break;
        if(ptr->next->id == value) {
            parent = ptr;
        }
        ptr = ptr->next;
    }
    if(parent != NULL) { /* Case: Delete "middle" or end node */
        Node *del = parent->next;
        parent->next = del->next;
        del->next = ptr->next;
        ptr->next = del;
        del->id = -1;
        cache->used--;
        pthread_mutex_unlock(cache->locker);
        return 0;
    }
    pthread_mutex_unlock(cache->locker);
    return -1; /* Case: Value not found in cache */
}

int MTL_size(MTCache *cache) {
    pthread_mutex_lock(cache->locker);
    int used = cache->used;
    pthread_mutex_unlock(cache->locker);
    return used;
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