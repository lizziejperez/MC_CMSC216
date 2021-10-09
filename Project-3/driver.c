#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

#define MAX 20

int main() {
	bst tree;
	int status;
    char *dst, *value;

/*bst_create*/
	/*PASSED*/
	puts("Testing bst_create:");
	status = bst_create(&tree);
	if(status!=BST_SUCCESS) printf("%d error", status);
	if(tree.count!=0) puts("tree count wrong value");
	if(tree.head!=NULL) puts("tree head not null");
	if(tree.curr!=NULL) puts("tree curr not null");
	puts(".");

/*bst_insert*/
	/*PASSED*/
	puts("Testing bst_insert (1):");
	status = bst_insert(&tree, "Howdy!");
	if(status!=BST_SUCCESS) printf("%d error\n", status);
	puts(".");
	/*PASSED*/
	puts("Testing bst_insert (2):");
	status = bst_insert(&tree, "What's up?");
	if(status!=BST_SUCCESS) printf("s1 %d error\n", status);
	status = bst_insert(&tree, "Game on.");
	if(status!=BST_SUCCESS) printf("s2 %d error\n", status);
	status = bst_insert(&tree, "No way..");
	if(status!=BST_SUCCESS) printf("s3 %d error\n", status);
	status = bst_insert(&tree, "I don't know.");
	if(status!=BST_SUCCESS) printf("s4 %d error\n", status);
	puts(".");
	/*PASSED*/
	puts("Testing bst_insert (3):");
	status = bst_insert(&tree, "Howdy!");
	if(status!=BST_SUCCESS) printf("%d error", status);
	puts(".");

/*bst_first*/
	/*PASSED*/
	puts("Testing bst_first:");
	dst = malloc(sizeof(char)*MAX);
	status = bst_first(&tree, dst);
	if(status!=BST_SUCCESS)
		printf("%d error\n", status);
	else
		printf("result: %s\nexpected: Game on.\n", dst);
	free(dst);
	puts(".");

/*bst_last*/
	/*PASSED*/
	puts("Testing bst_last:");
	dst = malloc(sizeof(char)*MAX);
	status = bst_last(&tree, dst);
	if(status!=BST_SUCCESS)
		printf("%d error\n", status);
	else
		printf("result: %s\nexpected: What's up?\n", dst);
	free(dst);
	puts(".");

/*bst_next*/
	/*PASSED*/
	puts("Testing bst_next (1):");
	dst = malloc(sizeof(char)*MAX);
	status = bst_next(&tree, dst);
	if(status!=BST_ERR_NULL_POINTER) printf("%d error\n", status);
	free(dst);
	puts(".");

/*bst_previous*/
	/*PASSED*/
	puts("Testing bst_previous (1):");
	dst = malloc(sizeof(char)*MAX);
	status = bst_previous(&tree, dst);
	if(status!=BST_ERR_NULL_POINTER) printf("%d error\n", status);
	free(dst);
	puts(".");

/*bst_find*/
	/*PASSED*/
	puts("Testing bst_find (1):");
	value = "Nothing";
	status = bst_find(&tree, value);
	if(status!=BST_ERR_NOT_FOUND) printf("%d error", status);
	puts(".");
	/*PASSED*/
	puts("Testing bst_find (2):");
	value = "What's up?";
	status = bst_find(&tree, value);
	if(status!=BST_SUCCESS) printf("%d error", status);
	puts(".");
	/*PASSED*/
	puts("Testing bst_find (3):");
	value = "Howdy!";
	status = bst_find(&tree, value);
	if(status!=BST_SUCCESS) printf("%d error", status);
	puts(".");

/*bst_next*/
	/*PASSED*/
	puts("Testing bst_next (2):");
	dst = malloc(sizeof(char)*MAX);
	status = bst_next(&tree, dst);
	if(status!=BST_SUCCESS)
		printf("%d error\n", status);
	else
		printf("result: %s\nexpected: What's up?\n", dst);
	free(dst);

/*bst_find*/
	/*PASSED*/
	puts("Testing bst_find (4):");
	value = "Howdy!";
	status = bst_find(&tree, value);
	if(status!=BST_SUCCESS) printf("%d error", status);
	puts(".");

/*bst_previous*/
	/*PASSED*/
	puts("Testing bst_previous (2):");
	dst = malloc(sizeof(char)*MAX);
	status = bst_previous(&tree, dst);
	if(status!=BST_SUCCESS)
		printf("%d error\n", status);
	else
		printf("result: %s\nexpected: Game on.\n", dst);
	free(dst);

/*TEST bst_remove*/
	/*puts("Testing bst_remove:");
	status = bst_remove(&tree);
	if(status!=BST_SUCCESS) printf("%d error", status);*/

/*TEST bst_destroy*/
	puts("Testing bst_destroy:");
	status = bst_destroy(&tree);
	if(status!=BST_SUCCESS) printf("%d error", status);

	puts("End of test.");
	return 0;
}