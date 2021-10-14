/*
** Name: Elizabeth Perez
** Student ID: eperez57
** M-number: M20966722
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

typedef struct node {
	char *val;
	int dcount;
	struct node *parent;
	struct node *next;
	struct node *prev;
} node; /* bst node */

int idx; /* the bst curr dcount "index" */

/*
** Returns ptr to the node to replace the node in the bst
*/
node *node_replace(node *theNode);
/*
** Frees every node under the initially given root node recursively
*/
void node_destroy(node *root);

int bst_create(bst *newTree) {
	if(newTree==NULL) return BST_ERR_MEM_ALLOC;
	*newTree = (bst){.count=0,.head=NULL,.curr=NULL};
	if((newTree->count!=0)||(newTree->head!=NULL)||(newTree->curr!=NULL)) return BST_ERR_UNKNOWN;
	return BST_SUCCESS;
}

int bst_insert(bst *theTree, char *value) {
	if(theTree==NULL) return BST_ERR_NULL_TREE;
	if(value==NULL) return BST_ERR_NULL_VALUE;
	node *curr = theTree->curr;
	if(bst_find(theTree, value)==BST_SUCCESS) {
		theTree->count++;
		theTree->curr->dcount++;
		theTree->curr = curr;
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
	newNode->parent = NULL;
	newNode->next = NULL;
	newNode->prev = NULL;
	newNode->dcount = 0;

	if((theTree->count==0)||(theTree->head==NULL)) {
		theTree->head = newNode;
		theTree->count++;
		return BST_SUCCESS;
	}

	theTree->curr = theTree->head;
	while(theTree->curr!=NULL) {
		if(strcmp(newNode->val, theTree->curr->val)>0) {
			if(theTree->curr->next==NULL) {
				newNode->parent = theTree->curr;
				theTree->curr->next = newNode;
				theTree->count++;
				theTree->curr = curr;
				return BST_SUCCESS;
			}
			theTree->curr = theTree->curr->next;
		} else {
			if(theTree->curr->prev==NULL) {
				newNode->parent = theTree->curr;
				theTree->curr->prev = newNode;
				theTree->count++;
				theTree->curr = curr;
				return BST_SUCCESS;
			}
			theTree->curr = theTree->curr->prev;
		}
	}
	theTree->curr = curr;
	return BST_ERR_UNKNOWN;
}

int bst_first(bst *theTree, char *dst) {
	if(theTree==NULL||theTree->head==NULL) return BST_ERR_NULL_TREE;
	node *curr = theTree->curr;
	theTree->curr = theTree->head;
	while(theTree->curr!=NULL) {
		if(theTree->curr->prev==NULL) {
			strcpy(dst, theTree->curr->val);
			if(strcmp(dst, theTree->curr->val)!=0) {
				theTree->curr = curr;
				return BST_ERR_UNKNOWN;
			}
			idx = 0;
			return BST_SUCCESS;
		}
		theTree->curr = theTree->curr->prev;
	}
	theTree->curr = curr;
	return BST_ERR_UNKNOWN;
}

int bst_next(bst *theTree, char *dst) {
	if(theTree==NULL||theTree->head==NULL) return BST_ERR_NULL_TREE;
	if(theTree->curr==NULL) return BST_ERR_NULL_POINTER;

	if(idx<theTree->curr->dcount) {
		idx++;
		strcpy(dst, theTree->curr->val);
		return BST_SUCCESS;
	}
	
	node *n = theTree->curr->next;
	if(n!=NULL){
		while(n->prev!=NULL) {
			n = n->prev;
		}
		strcpy(dst, n->val);
		theTree->curr = n;
		idx = 0;
		return BST_SUCCESS;
	}

	n = theTree->curr;
	while(n->parent!=NULL) {
		if(n->parent->prev == n) {
			strcpy(dst, n->parent->val);
			theTree->curr = n->parent;
			idx = 0;
			return BST_SUCCESS;
		}
		n = n->parent;
	}

	return BST_ERR_NOT_FOUND;
}

int bst_previous(bst *theTree, char *dst) {
	if(theTree==NULL||theTree->head==NULL) return BST_ERR_NULL_TREE;
	if(theTree->curr==NULL) return BST_ERR_NULL_POINTER;

	if(idx>0) {
		idx--;
		strcpy(dst, theTree->curr->val);
		return BST_SUCCESS;
	}

	node *n = theTree->curr->prev;
	if(n!=NULL){
		while(n->next!=NULL) {
			n = n->next;
		}
		strcpy(dst, n->val);
		theTree->curr = n;
		idx = theTree->curr->dcount;
		return BST_SUCCESS;
	}

	n = theTree->curr;
	while(n->parent!=NULL) {
		if(n->parent->next == n) {
			strcpy(dst, n->parent->val);
			theTree->curr = n->parent;
			idx = theTree->curr->dcount;
			return BST_SUCCESS;
		}
		n = n->parent;
	}

	return BST_ERR_NOT_FOUND;
}

int bst_last(bst *theTree, char *dst) {
	if(theTree==NULL||theTree->head==NULL) return BST_ERR_NULL_TREE;
	node *curr = theTree->curr;
	theTree->curr = theTree->head;
	while(theTree->curr!=NULL) {
		if(theTree->curr->next==NULL) {
			strcpy(dst, theTree->curr->val);
			if(strcmp(dst, theTree->curr->val)!=0) {
				theTree->curr = curr;
				return BST_ERR_UNKNOWN;
			}
			idx = theTree->curr->dcount;
			return BST_SUCCESS;
		}
		theTree->curr = theTree->curr->next;
	}
	theTree->curr = curr;
	return BST_ERR_UNKNOWN;
}

int bst_find(bst *theTree, char *value) {
	if(theTree==NULL||theTree->head==NULL) return BST_ERR_NULL_TREE;
	if(value==NULL) return BST_ERR_NULL_VALUE;
	node *root = theTree->head;
	while(root!=NULL) {
		if(strcmp(value, root->val)==0) {
			theTree->curr = root;
			idx = 0;
			return BST_SUCCESS;
		}
		root = (strcmp(value, root->val)>0) ? root->next : root->prev;
	}
	return BST_ERR_NOT_FOUND;
}

node *node_replace(node *theNode) {
	if((theNode->next==NULL)&&(theNode->prev==NULL)) return NULL;
			
	if((theNode->next!=NULL)&&(theNode->prev!=NULL)) {
		node *nroot = theNode->next;
		node *replacement;

		if(nroot->prev==NULL) {
			replacement = nroot;
			replacement->prev = theNode->prev;
			replacement->prev->parent = replacement;
			replacement->parent = theNode->parent;
			return replacement;
		}

		while(nroot->prev->prev!=NULL) nroot = nroot->prev;
		replacement = nroot->prev;
		nroot->prev = NULL;
		replacement->prev = theNode->prev;
		replacement->prev->parent = replacement;
		replacement->next = theNode->next;
		replacement->next->parent = replacement;
		replacement->parent = theNode->parent;
		return replacement;
	}

	if(theNode->next!=NULL){
		theNode->next->parent = theNode->parent;
		return theNode->next;
	} else {
		theNode->prev->parent = theNode->parent;
		return theNode->prev;
	}
}

int bst_remove(bst *theTree, char *value) {
	node *curr = theTree->curr;
	int find_status = bst_find(theTree, value);
	if(find_status!=BST_SUCCESS) return find_status;

	if(theTree->curr->dcount>0) {
		theTree->curr->dcount--;
		theTree->curr = curr;
		theTree->count--;
		return BST_SUCCESS;
	}

	if(theTree->head==theTree->curr)
		theTree->head = node_replace(theTree->curr);
	else if(theTree->curr==theTree->curr->parent->next)
		theTree->curr->parent->next = node_replace(theTree->curr);
	else
		theTree->curr->parent->prev = node_replace(theTree->curr);

	free(theTree->curr->val);
	free(theTree->curr);
	theTree->curr = curr;
	theTree->count--;
	return BST_SUCCESS;
}

void node_destroy(node *root) {
	if(root!=NULL) {
		node_destroy(root->prev);
		node_destroy(root->next);
		free(root->val);
		free(root);
	}
}

int bst_destroy(bst *theTree) {
	if(theTree==NULL||theTree->head==NULL) return BST_ERR_NULL_TREE;
	node_destroy(theTree->head);
	theTree->count = 0;
	theTree->head = NULL;
	theTree->curr = NULL;
	return BST_SUCCESS;
}