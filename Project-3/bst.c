#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char *val;
	struct node *next;
	struct node *prev;
} node;

typedef struct bst {
	int count;
	struct node *head;
	struct node *curr;
} bst;

#define BST_SUCCESS            1
#define BST_ERR_UNKNOWN        0
#define BST_ERR_NULL_POINTER  -1
#define BST_ERR_NULL_TREE     -2
#define BST_ERR_NULL_VALUE    -4
#define BST_ERR_MEM_ALLOC     -8
#define BST_ERR_MEM_FREE     -16
#define BST_ERR_NOT_FOUND    -32

int bst_create(bst *newTree) {
	newTree->count = 0;
	newTree->head = NULL;
	newTree->curr = NULL;
	return BST_SUCCESS;
}

int bst_insert(bst *theTree, char *value) {
	node *newNode = malloc(sizeof(node));
	int len = 0;
	while(1) {
		if(*(value+len) == 0) break;
		len++;
	}
	len++;
	newNode->val = malloc(sizeof(char) * len);
	strcpy(newNode->val, value);

	if(theTree->count == 0) {
		theTree->head = newNode;
	} else {
		/**/
	}
	theTree->count++;
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