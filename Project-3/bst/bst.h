#ifndef _BST_H
#define _BST_H

/*
 * bst.h
 * Binary Search Trees Header File
 * CMSC 216 Project 3
 * Copyright Sandro Fouche 2021
 *
 */


typedef struct bst {
	int count;
	struct node *head;
	struct node *curr;
} bst;

/* 
 * Failure Codes
 */

#define BST_SUCCESS            1
#define BST_ERR_UNKNOWN        0
#define BST_ERR_NULL_POINTER  -1
#define BST_ERR_NULL_TREE     -2
#define BST_ERR_NULL_VALUE    -4
#define BST_ERR_MEM_ALLOC     -8
#define BST_ERR_MEM_FREE     -16
#define BST_ERR_NOT_FOUND    -32



/* bst_create() - takes a pointer to a binary search tree, and initializes
 * the tree data structure.
 * bst_create() returns BST_SUCCESS for success or one of the
 * above failure codes.
 */ 
int bst_create(bst *newTree);



/* bst_insert() - takes a pointer to a previously initialized bst, and adds a
 * node that contains "value" to the tree.  bst_insert()
 * should allocate space for, and copy the contents of "value" into the
 * node.  bst_insert() returns BST_SUCCESS for success or one of the
 * above failure codes.
 */ 
int bst_insert(bst *theTree, char *value);



/* bst_first() - takes a pointer to a previously initialized bst, and a pointer
 * to a string to be modified.  bst_first() should copy the value of the
 * lowest valued node into string pointed to by "dst".  bst_first() should
 * also update the current node pointed to by the bst.  bst_first() should
 * not allocate any space for dst.  bst_first() returns BST_SUCCESS
 * indicating the number or bytes copied to "dst" or one of the above
 * failure codes.
 */ 
int bst_first(bst *theTree, char *dst);


/* bst_next() - takes a pointer to a previously initialized bst, and a pointer
 * to a string to be modified.  bst_next() should copy the value of the node
 * that succeeds the node previously returned by first, previous, next, or find
 * into string pointed to by "dst".  bst_next() should not allocate any
 * space for "dst".  bst_next() should also update the current node
 * pointed to by the bst.  bst_next() returns BST_SUCCESS
 * or one of the above failure codes.
 */ 
int bst_next(bst *theTree, char *dst);


/* bst_previous() - takes a pointer to a previously initialized bst, and a pointer
 * to a string to be modified.  bst_previous() should copy the value of the node
 * that preceeds the node previously returned by last, previous, next, or find
 * into string pointed to by "dst".  bst_previous() should not allocate any
 * space for "dst".  bst_previous() should also update the current node
 * pointed to by the bst.  bst_previous() returns BST_SUCCESS
 * or one of the above failure codes.
 */ 
int bst_previous(bst *theTree, char *dst);


/* bst_last() - takes a pointer to a previously initialized bst, and a pointer
 * to a string to be modified.  bst_last() should copy the value of the
 * highest valued node into string pointed to by "dst".  bst_last() should
 * not allocate any space for dst.  bst_last() should also update the
 * current node pointed to by the bst.  bst_last() returns BST_SUCCESS
 * or one of the above failure codes.
 */ 
int bst_last(bst *theTree, char *dst);


/* bst_find() - takes a pointer to a previously initialized bst, and a pointer
 * to a string to be found.  bst_find() searches the bst for node that
 * matches "value" and if found updates the current node pointed to by
 * the bst.  bst_last() returns BST_SUCCESS indicating success or
 * one of the above failure codes.
 */ 
int bst_find(bst *theTree, char *value);



/* bst_remove() - takes a pointer to a previously initialized bst, and deletes
 * a node that contains "value" from the tree.  bst_remove() should
 * de-allocate space for the contents of the node and its value.  bst_remove()
 * returns BST_SUCCESS for success or one of the above failure codes.
 */ 
int bst_remove(bst *theTree, char *value);



/* bst_destroy() - takes a pointer to a previously initialized bst, and
 * deallocates any created nodes.  bst_destroy() should de-allocate any remaining nodes
 * of "theTree".  bst_destroy() returns BST_SUCCESS for success or
 * one of the above failure codes.
 */ 
int bst_destroy(bst *theTree);

#endif /* _BST_H */
