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
	if(theTree->head==NULL) return BST_ERR_NULL_TREE;
	node *newNode = malloc(sizeof(node));
	if(newNode==NULL) return BST_ERR_MEM_ALLOC;
	int len = 0;
	while(1) {
		if(*(value+len)==0) break;
		len++;
	}
	len++;
	newNode->val = malloc(sizeof(char) * len);
	if(newNode->val==NULL) return BST_ERR_MEM_ALLOC;
	strcpy(newNode->val, value);

	theTree->curr = theTree->head;
	while(theTree->curr!=NULL) {
		if(strcmp(value, theTree->curr) < 0) {
			if(theTree->curr->next==NULL) {
				theTree->curr->next = newNode;
				theTree->count++;
				return BST_SUCCESS;
			}
			theTree->curr = theTree->curr->next;
		} else {
			if(theTree->curr->prev==NULL) {
				theTree->curr->prev = newNode;
				theTree->count++;
				return BST_SUCCESS;
			}
			theTree->curr = theTree->curr->prev;
		}
	}
	return BST_ERR_UNKNOWN;
}

int bst_first(bst *theTree, char *dst) {
	if(theTree->head==NULL) return BST_ERR_NULL_TREE;
	theTree->curr = theTree->head->prev;
	while(theTree->curr!=NULL) {
		if(theTree->curr->prev==NULL) break;
		theTree->curr = theTree->curr->prev;
	}
	if(theTree->head==NULL) return BST_ERR_NULL_TREE;
	if(theTree->curr==NULL) return BST_ERR_UNKNOWN;
	strcpy(dst, theTree->curr->val);
	return BST_SUCCESS;
}

int bst_next(bst *theTree, char *dst) {
	if(theTree->head==NULL) return BST_ERR_NULL_TREE;
	dst = theTree->curr->next->val;
	theTree->curr = theTree->curr->next;
	return BST_SUCCESS;
}

int bst_previous(bst *theTree, char *dst) {
	if(theTree->head==NULL) return BST_ERR_NULL_TREE;
	dst = theTree->curr->prev->val;
	theTree->curr = theTree->curr->prev;
	return BST_SUCCESS;
}

int bst_last(bst *theTree, char *dst) {
	if(theTree->head==NULL) return BST_ERR_NULL_TREE;
	theTree->curr = theTree->head->next;
	while(theTree->curr!=NULL) {
		if(theTree->curr->next==NULL) break;
		theTree->curr = theTree->curr->next;
	}
	if(theTree->curr==NULL) return BST_ERR_UNKNOWN;
	strcpy(dst, theTree->curr->val);
	return BST_SUCCESS;
}

int bst_find(bst *theTree, char *value) {
	if(theTree->head==NULL) return BST_ERR_NULL_TREE;
	theTree->curr = theTree->head;
	while(theTree->curr!=NULL) {
		if(strcmp(value, theTree->curr) == 0)
			return BST_SUCCESS;
		if(strcmp(value, theTree->curr) < 0)
			theTree->curr = theTree->curr->next;
		else
			theTree->curr = theTree->curr->prev;
	}
	return BST_ERR_NOT_FOUND;
}

int bst_remove(bst *theTree, char *value) {
	if(theTree->head==NULL) return BST_ERR_NULL_TREE;
	while(bst_find(theTree, value)) {
		node *next = theTree->curr->next;
		node *prev = theTree->curr->prev;
		/*code*/
	}
}

int bst_destroy(bst *theTree) {
	char *dst;
	while(bst_first(theTree, dst)) {
		bst_remove(theTree, dst);
	}
	while(theTree->curr!=NULL) {
		node *root = theTree->curr;
		theTree->curr = theTree->curr->next;
		bst_destroy(theTree);
		theTree->curr = theTree->curr->prev;
		bst_destroy(theTree);
		free(root->val);
		free(root);
	}
	return BST_SUCCESS;
}