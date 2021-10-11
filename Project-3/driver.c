#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

#define MAX 20

void test1();
void test2();
void test3();
void test4();
void test5();

int main() {
	/*test1();
	test2();
	test3();*/
	test4();
	test5();

	return 0;
}

void test1() {
	bst tree;
	int status;

	puts("TEST 1: create, insert, destroy");

	puts("Testing create:");
	status = bst_create(&tree);
	if(status!=BST_SUCCESS) printf("%d error", status);
	if(tree.count!=0) puts("tree count wrong value");
	if(tree.head!=NULL) puts("tree head not null");
	if(tree.curr!=NULL) puts("tree curr not null");

	puts("Testing insert (1):");
	status = bst_insert(&tree, "Howdy!");
	if(status!=BST_SUCCESS) printf("%d error\n", status);

	puts("Testing insert (2):");
	status = bst_insert(&tree, "What's up?");
	if(status!=BST_SUCCESS) printf("s1 %d error\n", status);
	status = bst_insert(&tree, "Game on.");
	if(status!=BST_SUCCESS) printf("s2 %d error\n", status);
	status = bst_insert(&tree, "No way..");
	if(status!=BST_SUCCESS) printf("s3 %d error\n", status);
	status = bst_insert(&tree, "I don't know.");
	if(status!=BST_SUCCESS) printf("s4 %d error\n", status);

	puts("Testing insert (3):");
	status = bst_insert(&tree, "Howdy!");
	if(status!=BST_SUCCESS) printf("%d error", status);

	puts("Testing destroy:");
	status = bst_destroy(&tree);
	if(status!=BST_SUCCESS) printf("%d error", status);

	puts("--------------------");
}

void test2() {
	bst tree;
	int status;
	char *dst;

	puts("TEST 2: first, last");
	bst_create(&tree);
	bst_insert(&tree, "Howdy!");
	bst_insert(&tree, "What's up?");
	bst_insert(&tree, "Game on.");
	bst_insert(&tree, "No way..");
	bst_insert(&tree, "I don't know.");
	bst_insert(&tree, "Howdy!");

	puts("Testing first:");
	dst = malloc(sizeof(char)*MAX);
	status = bst_first(&tree, dst);
	if(status!=BST_SUCCESS)
		printf("%d error\n", status);
	else
		printf("result: %s\nexpected: Game on.\n", dst);
	free(dst);

	puts("Testing last:");
	dst = malloc(sizeof(char)*MAX);
	status = bst_last(&tree, dst);
	if(status!=BST_SUCCESS)
		printf("%d error\n", status);
	else
		printf("result: %s\nexpected: What's up?\n", dst);
	free(dst);

	bst_destroy(&tree);
	puts("--------------------");
}

void test3() {
	bst tree;
	int status;
	char *value;

	puts("TEST 3: find");
	bst_create(&tree);
	bst_insert(&tree, "Howdy!");
	bst_insert(&tree, "What's up?");
	bst_insert(&tree, "Game on.");
	bst_insert(&tree, "No way..");
	bst_insert(&tree, "I don't know.");
	bst_insert(&tree, "Howdy!");

	puts("Testing find (1):");
	value = "N/A";
	status = bst_find(&tree, value);
	if(status!=BST_ERR_NOT_FOUND) printf("%d error", status);

	puts("Testing find (2):");
	value = "What's up?";
	status = bst_find(&tree, value);
	if(status!=BST_SUCCESS) printf("%d error", status);

	puts("Testing find (3):");
	value = "Howdy!";
	status = bst_find(&tree, value);
	if(status!=BST_SUCCESS) printf("%d error", status);

	bst_destroy(&tree);
	puts("--------------------");
}

void test4() {
	bst tree;
	int status;
	char *dst, *value;

	puts("TEST 4: next, previous");
	bst_create(&tree);
	bst_insert(&tree, "Howdy!");
	bst_insert(&tree, "What's up?");
	bst_insert(&tree, "Game on.");
	bst_insert(&tree, "No way..");
	bst_insert(&tree, "I don't know.");
	bst_insert(&tree, "Howdy!");

	puts("Testing next (1):");
	dst = malloc(sizeof(char)*MAX);
	status = bst_next(&tree, dst);
	if(status!=BST_ERR_NULL_POINTER) printf("%d error\n", status);
	if(status==BST_SUCCESS) printf("result: %s\nnot expected result\n", dst);
	free(dst);

	puts("Testing previous (1):");
	dst = malloc(sizeof(char)*MAX);
	status = bst_previous(&tree, dst);
	if(status!=BST_ERR_NULL_POINTER) printf("%d error\n", status);
	if(status==BST_SUCCESS) printf("result: %s\nnot expected result\n", dst);
	free(dst);

	value = "Howdy!";
	bst_find(&tree, value);

	puts("Testing next (2):");
	dst = malloc(sizeof(char)*MAX);
	status = bst_next(&tree, dst);
	if(status!=BST_SUCCESS)
		printf("%d error\n", status);
	else
		printf("result: %s\nexpected: What's up?\n", dst);
	free(dst);

	bst_find(&tree, value);

	puts("Testing previous (2):");
	dst = malloc(sizeof(char)*MAX);
	status = bst_previous(&tree, dst);
	if(status!=BST_SUCCESS)
		printf("%d error\n", status);
	else
		printf("result: %s\nexpected: Game on.\n", dst);
	free(dst);

	bst_destroy(&tree);
	puts("--------------------");
}

void test5() {
	bst tree;
	int status;
	char *value;

	puts("TEST 5: remove");
	bst_create(&tree);
	bst_insert(&tree, "Howdy!");
	bst_insert(&tree, "What's up?");
	bst_insert(&tree, "Game on.");
	bst_insert(&tree, "No way..");
	bst_insert(&tree, "I don't know.");
	bst_insert(&tree, "Howdy!");

	puts("Testing remove (1):");
	value = "Game on.";
	status = bst_remove(&tree, value);
	if(status!=BST_SUCCESS) printf("%d error", status);

	bst_destroy(&tree);
	bst_create(&tree);
	bst_insert(&tree, "Howdy!");
	bst_insert(&tree, "What's up?");
	bst_insert(&tree, "Game on.");
	bst_insert(&tree, "No way..");
	bst_insert(&tree, "I don't know.");
	bst_insert(&tree, "Howdy!");

	puts("Testing remove (2):");
	value = "Nothing";
	status = bst_remove(&tree, value);
	if(status!=BST_ERR_NOT_FOUND) printf("%d error", status);

	bst_destroy(&tree);
	bst_create(&tree);
	bst_insert(&tree, "Howdy!");
	bst_insert(&tree, "What's up?");
	bst_insert(&tree, "Game on.");
	bst_insert(&tree, "No way..");
	bst_insert(&tree, "I don't know.");
	bst_insert(&tree, "Howdy!");

	puts("Testing remove (3):");
	value = "Howdy!";
	status = bst_remove(&tree, value);
	if(status!=BST_SUCCESS) printf("%d error", status);
	status = bst_remove(&tree, value);
	if(status!=BST_SUCCESS) printf("%d error", status);
	puts("--------------------");
}

void alphSetup(bst *tree) {
	bst_create(tree);
	bst_insert(tree, "M");
	bst_insert(tree, "G");
	bst_insert(tree, "S");
	bst_insert(tree, "A");
	bst_insert(tree, "Z");
	bst_insert(tree, "D");
	bst_insert(tree, "W");
	bst_insert(tree, "C");
	bst_insert(tree, "E");
	bst_insert(tree, "V");
	bst_insert(tree, "X");
	/*       M
	*    ___/ \___
	*   G         S
	*  / \       / \
	* A   D     W   Z
	*    / \   / \
	*   C   E V   X
	*/
}