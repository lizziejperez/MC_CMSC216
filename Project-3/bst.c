#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

typedef struct node {
	char *val;
	int dcount; /*duplicate count*/
	struct node *next;
	struct node *prev;
} node;

int bst_create(bst *newTree) {
	newTree = malloc(sizeof(bst));
	if(newTree==NULL) return BST_ERR_MEM_ALLOC;
	newTree->count = 0;
	newTree->head = NULL;
	newTree->curr = NULL;
	return BST_SUCCESS;
}

int bst_insert(bst *theTree, char *value) {
	if(value==NULL) return BST_ERR_NULL_VALUE;
	if(bst_find(theTree, value)==BST_SUCCESS) {
		theTree->curr->dcount++;
		return BST_SUCCESS;
	}

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
	if(strcmp(newNode->val, value)!=0) return BST_ERR_UNKNOWN;
	newNode->next = NULL;
	newNode->prev = NULL;
	newNode->dcount = 0;

	if(theTree->count==0) {
		theTree->head = newNode;
		theTree->count++;
		return BST_SUCCESS;
	}

	if(theTree->head==NULL) return BST_ERR_NULL_TREE;
	theTree->curr = theTree->head;
	while(theTree->curr!=NULL) {
		if(strcmp(newNode->val, theTree->curr)>0) {
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

/*Q: Should theTree->curr only be updated if method is successful? yes*/
int bst_first(bst *theTree, char *dst) {
	if(theTree->head==NULL) return BST_ERR_NULL_TREE;
	theTree->curr = theTree->head;
	while(theTree->curr!=NULL) {
		if(theTree->curr->prev==NULL) {
			strcpy(dst, theTree->curr->val);
			if(strcmp(dst, theTree->curr->val)!=0) return BST_ERR_UNKNOWN;
			return BST_SUCCESS;
		}
		theTree->curr = theTree->curr->prev;
	}
	return BST_ERR_UNKNOWN;
}

int bst_next(bst *theTree, char *dst) {
	if(theTree->head==NULL) return BST_ERR_NULL_TREE;
	if(theTree->curr->next==NULL) return BST_ERR_NULL_POINTER;
	strcpy(dst, theTree->curr->next->val);
	if(strcmp(dst, theTree->curr->next->val)!=0) return BST_ERR_UNKNOWN;
	theTree->curr = theTree->curr->next;
	return BST_SUCCESS;
}

int bst_previous(bst *theTree, char *dst) {
	if(theTree->head==NULL) return BST_ERR_NULL_TREE;
	if(theTree->curr->next==NULL) return BST_ERR_NULL_POINTER;
	strcpy(dst, theTree->curr->prev->val);
	if(strcmp(dst, theTree->curr->prev->val)!=0) return BST_ERR_UNKNOWN;
	theTree->curr = theTree->curr->prev;
	return BST_SUCCESS;
}

/*Q: Should theTree->curr only be updated if method is successful? yes*/
int bst_last(bst *theTree, char *dst) {
	if(theTree->head==NULL) return BST_ERR_NULL_TREE;
	theTree->curr = theTree->head;
	while(theTree->curr!=NULL) {
		if(theTree->curr->next==NULL) {
			strcpy(dst, theTree->curr->val);
			if(strcmp(dst, theTree->curr->val)!=0) return BST_ERR_UNKNOWN;
			return BST_SUCCESS;
		}
		theTree->curr = theTree->curr->next;
	}
	return BST_ERR_UNKNOWN;
}

int bst_find(bst *theTree, char *value) {
	if(theTree->head==NULL) return BST_ERR_NULL_TREE;
	if(value==NULL) return BST_ERR_NULL_VALUE;
	node *root = theTree->head;
	while(root!=NULL) {
		if(strcmp(value, root->val)==0) {
			theTree->curr = root;
			return BST_SUCCESS;
		}
		root = (strcmp(value, root->val)>0) ? theTree->curr->next : theTree->curr->prev;
	}
	return BST_ERR_NOT_FOUND;
}

/*
** Returns ptr to the node to replace the removed node in the bst
*/
node *remove(node *theNode) {
	if((theNode->next==NULL)&&(theNode->prev==NULL)) return NULL;
			
	if((theNode->next!=NULL)&&(theNode->prev!=NULL)) {
		node *nroot = theNode->next;
		node *replacement;

		if(nroot->prev==NULL) {
			replacement = nroot;
			replacement->prev = theNode->prev;
			return replacement;
		}

		while(nroot->prev->prev!=NULL) nroot = nroot->prev;
		replacement = nroot->prev;
		nroot->prev = NULL;
		replacement->prev = theNode->prev;
		replacement->next = theNode->next;
		return replacement;
	}

	return (theNode->next!=NULL) ? theNode->next : theNode->prev;
}

int bst_remove(bst *theTree, char *value) {
	if(theTree->head==NULL) return BST_ERR_NULL_TREE;
	if(value==NULL) return BST_ERR_NULL_VALUE;

	node *root = theTree->head;

	while(root!=NULL) {
		if(strcmp(value, root->next->val)==0) {
			node *theNode = root->next;
			if(theNode->dcount>0){
				theNode->dcount--;
				return BST_SUCCESS;
			}
			root->next = remove(theNode);
			free(theNode->val);
			free(theNode);
			theTree->count--;
			return BST_SUCCESS;
		}

		if(strcmp(value, root->prev->val)==0) {
			node *theNode = root->prev;
			if(theNode->dcount>0){
				theNode->dcount--;
				return BST_SUCCESS;
			}
			root->prev = remove(theNode);
			free(theNode->val);
			free(theNode);
			theTree->count--;
			return BST_SUCCESS;
		}

		root = (strcmp(value, root->val)>0) ? root->next : root->prev;
	}
	return BST_ERR_NOT_FOUND;
}

void clear(node *root) {
	if(root!=NULL) {
		clear(root->next);
		clear(root->prev);
		free(root->val);
		free(root);
	}
}

int bst_destroy(bst *theTree) {
	clear(theTree->head);
	theTree->count = 0;
	theTree->head = NULL;
	theTree->curr = NULL;
	return BST_SUCCESS;
}