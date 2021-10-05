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
	if(value==NULL) return BST_ERR_NULL_VALUE;

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

/*Q: Should theTree->curr only be updated if method is successful?*/
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

/*Q: Should theTree->curr only be updated if method is successful?*/
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

/*Q: Should multiple instances of the same values all be removed?*/
int bst_remove(bst *theTree, char *value) {
	if(theTree->head==NULL) return BST_ERR_NULL_TREE;
	if(value==NULL) return BST_ERR_NULL_VALUE;

	node *root = theTree->head;
	node *theNode = NULL;

	while(root!=NULL) {
		int cmpNext = strcmp(value, root->next->val);
		if(cmpNext==0) {
			theNode = root->next;
			if((theNode->next==NULL)&&(theNode->prev==NULL)) {
				root->next = NULL;
			} else if((theNode->next!=NULL)&&(theNode->prev!=NULL)) {
				/*if the node has two children*/
				if(theNode->next->next==NULL) { /*if one right leaf*/
					theNode->next->prev = theNode->prev;
					root->next = theNode->next;
				} else {
					node *temp = theNode->next; /*storing right subtree*/
					while(temp->prev->prev!=NULL) {
						temp = temp->prev;
					} /*set temp to pointer to the parent of the 'smallest' node in right subtree*/
					root->next = temp->prev; /*replaced the node to remove with the 'smallest' node in right subtree*/
					root->next->prev = theNode->prev;
					root->next->next = theNode->next;
					temp->prev = NULL; /*removed parent pointer to 'smallest' node in right subtree*/
				}
			} else {
				root->next = (theNode->next!=NULL) ? theNode->next : theNode->prev;
			}
			free(theNode->val);
			free(theNode);
			theTree->count--;
		}

		int cmpPrev = strcmp(value, root->prev->val);
		if(cmpPrev==0) {
			theNode = root->prev;
			if((theNode->next==NULL)&&(theNode->prev==NULL)) {
				root->prev = NULL;
			} else if((theNode->next!=NULL)&&(theNode->prev!=NULL)) {
				/*if the node has two children*/
				if(theNode->next->next==NULL) { /*if one right leaf*/
					theNode->next->prev = theNode->prev;
					root->prev = theNode->next;
				} else {
					node *temp = theNode->next; /*storing right subtree*/
					while(temp->prev->prev!=NULL) {
						temp = temp->prev;
					} /*set temp to pointer to the parent of the 'smallest' node in right subtree*/
					root->prev= temp->prev; /*replaced the node to remove with the 'smallest' node in right subtree*/
					root->prev->prev = theNode->prev;
					root->prev->next = theNode->next;
					temp->prev = NULL; /*removed parent pointer to 'smallest' node in right subtree*/
				}
			} else {
				root->prev = (theNode->next!=NULL) ? theNode->next : theNode->prev;
			}
			free(theNode->val);
			free(theNode);
			theTree->count--;
		}

		root = (strcmp(value, root->val)>0) ? theNode->next : theNode->prev;
	}
	return BST_SUCCESS;
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