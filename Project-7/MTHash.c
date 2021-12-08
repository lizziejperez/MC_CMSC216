#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "MTHash.h"

typedef struct _Data {
	int data;
	struct _Data *next;
} Data;

typedef struct _HashNode {
    // int id;
	Data *dataBucket;
    pthread_mutex_t *locker;
	struct _HashNode *next;
	struct _HashNode *prev;
} HashNode;

typedef struct _mt_hashtable {
    HashNode *head;
    int tsize;
} MTHash;

MTHash *MTH_init(int tsize) {
    MTHash *hashTable = malloc(sizeof(MTHash));
    hashTable->head = NULL;
    hashTable->tsize = 0;

    while(hashTable->tsize < tsize) {
        if(hashTable->head == NULL) {
            hashTable->head = malloc(sizeof(HashNode));
            // hashTable->head->id = hashTable->tsize;
            hashTable->head->dataBucket = NULL;
            pthread_mutex_init(hashTable->head->locker, NULL);
            hashTable->head->next = NULL;
            hashTable->head->prev = NULL;
        } else {
            HashNode *ptr = hashTable->head;
            while(ptr->next != NULL)
                ptr = ptr->next;
            ptr->next = malloc(sizeof(HashNode));
            // ptr->next->id = hashTable->tsize;
            ptr->next->dataBucket = NULL;
            pthread_mutex_init(ptr->next->locker, NULL);
            ptr->next->next = NULL;
            ptr->next->prev = ptr;
        }
        hashTable->tsize++;
    }

    return hashTable;
}

int MTH_add(MTHash *hashTable, int value) {
    int hashResult = value % hashTable->tsize;
    HashNode *ptr = hashTable->head;
    for(int i = 0; i < hashResult; i++) {
        ptr = ptr->next;
    }

    if(ptr->dataBucket == NULL) {
        pthread_mutex_lock(ptr->locker);
        ptr->dataBucket = malloc(sizeof(Data));
        ptr->dataBucket->data = value;
        ptr->dataBucket->next = NULL;
        pthread_mutex_unlock(ptr->locker);
    } else {
        if(ptr->dataBucket->data == value) return -1;

        Data *ptr2 = ptr->dataBucket;
        while(ptr2->next != NULL) {
            ptr2 = ptr2->next;
            if(ptr2->data == value) return -1;
        }

        pthread_mutex_lock(ptr->locker);
        ptr2->next = malloc(sizeof(Data));
        ptr2->next->data = value;
        ptr2->next->next = NULL;
        pthread_mutex_unlock(ptr->locker);
    }
    

    return 0;
}

int MTH_delete(MTHash *hashTable, int value) {
    int hashResult = value % hashTable->tsize;
    HashNode *ptr = hashTable->head;
    for(int i = 0; i < hashResult; i++) {
        ptr = ptr->next;
    }

    if(ptr->dataBucket == NULL) return -1;
    
}