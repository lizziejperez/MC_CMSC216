# Project: Binary Search Trees
## Overview
Implement an API for Bianry Search Trees in C.
### Objectives
- Use C dynamica memory management functions - malloc & free
- Implement a data structure using structs and pointers
- Practice with recursion
## Description
### What to do
Create a C file called "bst.c" that implements binary search trees of strings.
Your implementation should make no assumptions about the number of nodes, or the eventual structure of the BST.
Therefore, you should use C dynamic memory allocation (malloc()) to create space for each node as necessary.
You should also clean-up nodes that are removed or destroyed using free().
Provided the header file "bst.h"; your project should implement all of the functions declared in the header file.
Specifically, you will be implementing:
```
int bst_create ( bst *newTree );
int bst_insert ( bst *theTree, char *value );
int bst_first ( bst *theTree, char *dst );
int bst_next ( bst *theTree, char *dst );
int bst_previous( bst *theTree, char *dst );
int bst_last ( bst *theTree, char *dst );
int bst_find ( bst *theTree, char *value );
int bst_remove ( bst *theTree, char *value );
int bst_destroy ( bst *theTree ); 
```
Your file will not run on it's own, but will need to be called from some other source file that contains a main().
For testing purposes, you might implement a small program (called a driver program) that exercises your binary search tree implementation.
## Compiling
```
gcc -Wall -pedantic-errors -Werror -c bst.c
gcc -Wall -pedantic-errors -Werror <driver.c> bst.o -o test_driver
```
