#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "MTHash.h"

typedef struct _Data {
	int data;
	struct _Data *next;
} Data;

typedef struct _HashNode {
	Data *dataBucket;
    pthread_mutex_t *locker;
	struct _HashNode *next;
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
            hashTable->head->dataBucket = NULL;
            pthread_mutex_init(hashTable->head->locker, NULL);
            hashTable->head->next = NULL;
        } else {
            HashNode *ptr = hashTable->head;
            while(ptr->next != NULL)
                ptr = ptr->next;
            ptr->next = malloc(sizeof(HashNode));
            ptr->next->dataBucket = NULL;
            pthread_mutex_init(ptr->next->locker, NULL);
            ptr->next->next = NULL;
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

    pthread_mutex_lock(ptr->locker);
    if(ptr->dataBucket == NULL) {
        ptr->dataBucket = malloc(sizeof(Data));
        ptr->dataBucket->data = value;
        ptr->dataBucket->next = NULL;
        pthread_mutex_unlock(ptr->locker);
        return 0;
    }

    if(ptr->dataBucket->data == value) {
        pthread_mutex_unlock(ptr->locker);
        return -1;
    }

    Data *ptr2 = ptr->dataBucket;
    while(ptr2->next != NULL) {
        ptr2 = ptr2->next;
        if(ptr2->data == value) {
            pthread_mutex_unlock(ptr->locker);
            return -1;
        }
    }
    ptr2->next = malloc(sizeof(Data));
    ptr2->next->data = value;
    ptr2->next->next = NULL;   
    pthread_mutex_unlock(ptr->locker);
    return 0;
}

int MTH_delete(MTHash *hashTable, int value) {
    int hashResult = value % hashTable->tsize;
    HashNode *ptr = hashTable->head; /* Bucket pointer */
    for(int i = 0; i < hashResult; i++) {
        ptr = ptr->next;
    }

    pthread_mutex_lock(ptr->locker);
    if(ptr->dataBucket == NULL) { /* Case: No data in the bucket */
        pthread_mutex_unlock(ptr->locker);
        return -1;
    }

    if(ptr->dataBucket->data == value) { /* Case: Delete head data */
        Data *next = ptr->dataBucket->next;
        free(ptr->dataBucket);
        ptr->dataBucket = next;
        pthread_mutex_unlock(ptr->locker);
        return 0;
    }

    Data *ptr2 = ptr->dataBucket; /* Parent data pointer */
    while(ptr2->next != NULL) {
        if(ptr2->next->data == value) { /* Case: Delete non-head data */
            Data *next = ptr2->next->next;
            free(ptr2->next);
            ptr2->next = next;
            pthread_mutex_unlock(ptr->locker);
            return 0;
        }
        ptr2 = ptr2->next;
    }

    pthread_mutex_unlock(ptr->locker);
    return -1;
}

int MTH_size(MTHash *hashTable) {
    int count = 0;
    for(int i = 0; i < hashTable->tsize; i++) {
        count += MTH_bucket_size(hashTable, i);
    }
    return count;
}

int MTH_bucket_size(MTHash *hashTable, int index) {
    HashNode *ptr = hashTable->head;
    for(int i = 0; i < index; i++) {
        ptr = ptr->next;
    }

    if(ptr->dataBucket == NULL) return 0;

    int count = 1;
    pthread_mutex_lock(ptr->locker);
    Data *ptr2 = ptr->dataBucket;
    while(ptr2->next != NULL) {
        count++;
        ptr2 = ptr2->next;
    }
    pthread_mutex_unlock(ptr->locker);
    return count;
}

void MTH_print(MTHash *hashTable) {
    HashNode *ptr = hashTable->head;
    for(int i = 0; i < hashTable->tsize; i++) {        
        pthread_mutex_lock(ptr->locker);
        Data *ptr2 = ptr->dataBucket;
        if(ptr2 != NULL) {
            printf("%d", ptr2->data);
            while(ptr2->next != NULL) {
                ptr2 = ptr2->next;
                printf(", %d", ptr2->data);
            }
        }
        printf("\n");
        pthread_mutex_unlock(ptr->locker);
        ptr = ptr->next;
    }
}