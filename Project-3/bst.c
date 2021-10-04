#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

typedef struct node {
	char *val;
	struct node *next;
	struct node *prev;
} node;

int bst_create(bst *newTree) {
	newTree->count = 0;
	newTree->head = NULL;
	newTree->curr = NULL;
	return BST_SUCCESS;
}

int bst_insert(bst *theTree, char *value) {
	node *newNode = malloc(sizeof(node));
	if(newNode==NULL) return BST_ERR_MEM_ALLOC;
	int len = 0;
	while(1) {
		if(*(value+len) == 0) break;
		len++;
	}
	len++;
	newNode->val = malloc(sizeof(char) * len);
	if(newNode->val==NULL) return BST_ERR_MEM_ALLOC;
	strcpy(newNode->val, value);

	theTree->curr->next = newNode;
	theTree->count++;
	theTree->curr = newNode;
	return BST_SUCCESS;
}

int bst_first(bst *theTree, char *dst) {

}

int bst_next(bst *theTree, char *dst) {

}

int bst_previous(bst *theTree, char *dst) {

}

int bst_last(bst *theTree, char *dst) {

}

int bst_find(bst *theTree, char *value) {

}

int bst_remove(bst *theTree, char *value) {

}

int bst_destroy(bst *theTree) {

}