#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

#define MAX 20

void test1();
void test2();
void test3();
void test4();
void test5();
void alphSetup(bst *tree);

int main() {
	test1();
	test2();
	test3();
	test4();
	test5();

	return 0;
}

void test1() {
	bst tree, tree2;
	int status;

	puts("TEST 1: create, insert, destroy");

	puts("Testing create:");

	puts("(Tree 1)");
	status = bst_create(&tree);
	if(status!=BST_SUCCESS) printf("%d error\n", status);
	if(tree.count!=0) puts("tree count wrong value");
	if(tree.head!=NULL) puts("tree head not null");
	if(tree.curr!=NULL) puts("tree curr not null");
	
	puts("(Tree 2)");
	status = bst_create(&tree2);
	if(status!=BST_SUCCESS) printf("%d error\n", status);
	if(tree.count!=0) puts("tree count wrong value");
	if(tree.head!=NULL) puts("tree head not null");
	if(tree.curr!=NULL) puts("tree curr not null");

	puts("Testing insert (1): head case");
	
	puts("(Tree 1)");
	status = bst_insert(&tree, "Howdy!");
	if(status!=BST_SUCCESS) printf("%d error\n", status);
	
	puts("(Tree 2)");
	status = bst_insert(&tree2, "M");
	if(status!=BST_SUCCESS) printf("%d error\n", status);

	puts("Testing insert (2): normal case");

	puts("(Tree 1)");
	status = bst_insert(&tree, "What's up?");
	if(status!=BST_SUCCESS) printf("s1 %d error\n", status);
	status = bst_insert(&tree, "Game on.");
	if(status!=BST_SUCCESS) printf("s2 %d error\n", status);
	status = bst_insert(&tree, "No way..");
	if(status!=BST_SUCCESS) printf("s3 %d error\n", status);
	status = bst_insert(&tree, "I don't know.");
	if(status!=BST_SUCCESS) printf("s4 %d error\n", status);

	puts("(Tree 2)");
	status = bst_insert(&tree2, "M");
	if(status!=BST_SUCCESS) printf("s1 %d error\n", status);
	status = bst_insert(&tree2, "G");
	if(status!=BST_SUCCESS) printf("s1 %d error\n", status);
	status = bst_insert(&tree2, "S");
	if(status!=BST_SUCCESS) printf("s1 %d error\n", status);
	status = bst_insert(&tree2, "A");
	if(status!=BST_SUCCESS) printf("s1 %d error\n", status);
	status = bst_insert(&tree2, "Z");
	if(status!=BST_SUCCESS) printf("s1 %d error\n", status);
	status = bst_insert(&tree2, "D");
	if(status!=BST_SUCCESS) printf("s1 %d error\n", status);
	status = bst_insert(&tree2, "W");
	if(status!=BST_SUCCESS) printf("s1 %d error\n", status);
	status = bst_insert(&tree2, "C");
	if(status!=BST_SUCCESS) printf("s1 %d error\n", status);
	status = bst_insert(&tree2, "E");
	if(status!=BST_SUCCESS) printf("s1 %d error\n", status);
	status = bst_insert(&tree2, "V");
	if(status!=BST_SUCCESS) printf("s1 %d error\n", status);
	status = bst_insert(&tree2, "X");
	if(status!=BST_SUCCESS) printf("s1 %d error\n", status);

	puts("Testing insert (3): duplicate case");

	puts("(Tree 1)");
	status = bst_insert(&tree, "Howdy!");
	if(status!=BST_SUCCESS) printf("%d error", status);

	puts("(Tree 2)");
	status = bst_insert(&tree2, "M");
	if(status!=BST_SUCCESS) printf("%d error", status);
	status = bst_insert(&tree2, "M");
	if(status!=BST_SUCCESS) printf("%d error", status);
	status = bst_insert(&tree2, "M");
	if(status!=BST_SUCCESS) printf("%d error", status);
	status = bst_insert(&tree2, "A");
	if(status!=BST_SUCCESS) printf("%d error", status);
	status = bst_insert(&tree2, "D");
	if(status!=BST_SUCCESS) printf("%d error", status);
	status = bst_insert(&tree2, "D");
	if(status!=BST_SUCCESS) printf("%d error", status);

	puts("Testing destroy:");

	puts("(Tree 1)");
	status = bst_destroy(&tree);
	if(status!=BST_SUCCESS) printf("%d error", status);

	puts("(Tree 2)");
	status = bst_destroy(&tree2);
	if(status!=BST_SUCCESS) printf("%d error", status);

	puts("--------------------");
}

void setup(bst *tree, bst *tree2) {
	/*       "Howdy!"(x2)
	*        /     \
	* "Game on." "What's up?"
	*             /
	*         "No way.."
	*           /
	* "I don't know."
	*/
	bst_create(tree);
	bst_insert(tree, "Howdy!");
	bst_insert(tree, "What's up?");
	bst_insert(tree, "Game on.");
	bst_insert(tree, "No way..");
	bst_insert(tree, "I don't know.");
	bst_insert(tree, "Howdy!");
	/*       M(x4)
	*    ___/ \______
	*   G__          S
	*  /   \        / \
	* A(x2) D(x3)  W   Z
	*      / \    / \
	*     C   E  V   X
	*/
	bst_create(tree2);
	bst_insert(tree2, "M");
	bst_insert(tree2, "G");
	bst_insert(tree2, "S");
	bst_insert(tree2, "A");
	bst_insert(tree2, "Z");
	bst_insert(tree2, "D");
	bst_insert(tree2, "W");
	bst_insert(tree2, "C");
	bst_insert(tree2, "E");
	bst_insert(tree2, "V");
	bst_insert(tree2, "X");
	bst_insert(tree2, "M");
	bst_insert(tree2, "M");
	bst_insert(tree2, "M");
	bst_insert(tree2, "A");
	bst_insert(tree2, "D");
	bst_insert(tree2, "D");
}

void test2() {
	bst tree, tree2;
	int status;
	char *dst;

	puts("TEST 2: first, last");
	setup(&tree, &tree2);
	puts("Testing first:");

	puts("(Tree 1)");
	dst = malloc(sizeof(char)*MAX);
	status = bst_first(&tree, dst);
	if(status!=BST_SUCCESS)
		printf("%d error\n", status);
	else
		printf("result: %s\nexpected: Game on.\n", dst);
	free(dst);

	puts("(Tree 2)");
	dst = malloc(sizeof(char)*2);
	status = bst_first(&tree2, dst);
	if(status!=BST_SUCCESS)
		printf("%d error\n", status);
	else
		printf("result: %s\nexpected: A\n", dst);
	free(dst);

	puts("Testing last:");

	puts("(Tree 1)");
	dst = malloc(sizeof(char)*MAX);
	status = bst_last(&tree, dst);
	if(status!=BST_SUCCESS)
		printf("%d error\n", status);
	else
		printf("result: %s\nexpected: What's up?\n", dst);
	free(dst);

	puts("(Tree 2)");
	dst = malloc(sizeof(char)*2);
	status = bst_last(&tree2, dst);
	if(status!=BST_SUCCESS)
		printf("%d error\n", status);
	else
		printf("result: %s\nexpected: Z\n", dst);
	free(dst);

	bst_destroy(&tree);
	bst_destroy(&tree2);
	puts("--------------------");
}

void test3() {
	bst tree, tree2;
	int status;
	char *value;

	puts("TEST 3: find");
	setup(&tree, &tree2);
	puts("Testing find (1): DNE case");

	puts("(Tree 1)");
	value = "N/A";
	status = bst_find(&tree, value);
	if(status!=BST_ERR_NOT_FOUND) printf("%d error\n", status);

	puts("(Tree 2)");
	value = "N/A";
	status = bst_find(&tree2, value);
	if(status!=BST_ERR_NOT_FOUND) printf("%d error\n", status);

	puts("Testing find (2): normal case");

	puts("(Tree 1)");
	value = "What's up?";
	status = bst_find(&tree, value);
	if(status!=BST_SUCCESS) printf("%d error\n", status);
	value = "Game on.";
	status = bst_find(&tree, value);
	if(status!=BST_SUCCESS) printf("%d error\n", status);

	puts("(Tree 2)");
	value = "D";
	status = bst_find(&tree, value);
	if(status!=BST_SUCCESS) printf("%d error\n", status);

	bst_destroy(&tree);
	bst_destroy(&tree2);
	puts("--------------------");
}

void test4() {
	bst tree, tree2;
	int status;
	char *dst, *value;

	puts("TEST 4: next, previous");
	setup(&tree, &tree2);
	puts("Testing next (1): no curr case");

	puts("(Tree 1)");
	dst = malloc(sizeof(char)*MAX);
	status = bst_next(&tree, dst);
	if(status!=BST_ERR_NULL_POINTER) printf("%d error\n", status);
	if(status==BST_SUCCESS) printf("result: %s\nnot expected result\n", dst);
	free(dst);

	puts("(Tree 2)");
	dst = malloc(sizeof(char)*2);
	status = bst_next(&tree2, dst);
	if(status!=BST_ERR_NULL_POINTER) printf("%d error\n", status);
	if(status==BST_SUCCESS) printf("result: %s\nnot expected result\n", dst);
	free(dst);

	puts("Testing previous (1): no curr case");

	puts("(Tree 1)");
	dst = malloc(sizeof(char)*MAX);
	status = bst_previous(&tree, dst);
	if(status!=BST_ERR_NULL_POINTER) printf("%d error\n", status);
	if(status==BST_SUCCESS) printf("result: %s\nnot expected result\n", dst);
	free(dst);

	puts("(Tree 2)");
	dst = malloc(sizeof(char)*2);
	status = bst_next(&tree2, dst);
	if(status!=BST_ERR_NULL_POINTER) printf("%d error\n", status);
	if(status==BST_SUCCESS) printf("result: %s\nnot expected result\n", dst);
	free(dst);

	puts("Testing next (2): normal case");

	puts("(Tree 1)");
	value = "Howdy!";
	bst_find(&tree, value);
	dst = malloc(sizeof(char)*MAX);
	status = bst_next(&tree, dst);
	if(status!=BST_SUCCESS)
		printf("%d error\n", status);
	else
		printf("result: %s\nexpected: What's up?\n", dst);
	free(dst);

	puts("(Tree 2)");
	value = "G";
	bst_find(&tree2, value);
	dst = malloc(sizeof(char)*2);
	status = bst_next(&tree2, dst);
	if(status!=BST_SUCCESS)
		printf("%d error\n", status);
	else
		printf("result: %s\nexpected: D\n", dst);
	free(dst);

	puts("Testing previous (2): normal case");

	puts("(Tree 1)");
	value = "Howdy!";
	bst_find(&tree, value);
	dst = malloc(sizeof(char)*MAX);
	status = bst_previous(&tree, dst);
	if(status!=BST_SUCCESS)
		printf("%d error\n", status);
	else
		printf("result: %s\nexpected: Game on.\n", dst);
	free(dst);

	puts("(Tree 2)");
	value = "G";
	bst_find(&tree2, value);
	dst = malloc(sizeof(char)*2);
	status = bst_previous(&tree2, dst);
	if(status!=BST_SUCCESS)
		printf("%d error\n", status);
	else
		printf("result: %s\nexpected: A\n", dst);
	free(dst);

	bst_destroy(&tree);
	bst_destroy(&tree2);
	puts("--------------------");
}

void test5() {
	bst tree, tree2;
	int status;
	char *value;

	puts("TEST 5: remove");
	setup(&tree, &tree2);
	puts("Testing remove (1): normal case");

	puts("(Tree 1)");
	value = "Game on."; /*no children*/
	status = bst_remove(&tree, value);
	if(status!=BST_SUCCESS) printf("%d error", status);
	value = "No way.."; /*one child*/
	status = bst_remove(&tree, value);
	if(status!=BST_SUCCESS) printf("%d error", status);

	puts("(Tree 2)");
	value = "G"; /*2 children*/
	status = bst_remove(&tree2, value);
	if(status!=BST_SUCCESS) printf("%d error", status);
	value = "C"; /*no children, but was descendent G*/
	status = bst_remove(&tree2, value);
	if(status!=BST_SUCCESS) printf("%d error", status);

	bst_destroy(&tree);
	bst_destroy(&tree2);
	setup(&tree, &tree2);
	puts("Testing remove (2): DNE case");

	puts("(Tree 1)");
	value = "Nothing";
	status = bst_remove(&tree, value);
	if(status!=BST_ERR_NOT_FOUND) printf("%d error", status);
	
	puts("(Tree 2)");
	value = "Nothing";
	status = bst_remove(&tree2, value);
	if(status!=BST_ERR_NOT_FOUND) printf("%d error", status);

	bst_destroy(&tree);
	bst_destroy(&tree2);
	setup(&tree, &tree2);
	puts("Testing remove (3): dupl case");

	puts("(Tree 1)");
	value = "Howdy!";
	status = bst_remove(&tree, value);
	if(status!=BST_SUCCESS) printf("%d error", status);
	status = bst_remove(&tree, value);
	if(status!=BST_SUCCESS) printf("%d error", status);
	status = bst_remove(&tree, value);
	if(status==BST_SUCCESS) puts("Unexpected success");

	puts("(Tree 2)");
	value = "D";
	status = bst_remove(&tree2, value);
	if(status!=BST_SUCCESS) printf("%d error", status);
	status = bst_remove(&tree2, value);
	if(status!=BST_SUCCESS) printf("%d error", status);
	status = bst_remove(&tree2, value);
	if(status!=BST_SUCCESS) printf("%d error", status);
	status = bst_remove(&tree2, value);
	if(status==BST_SUCCESS) puts("Unexpected success");

	bst_destroy(&tree);
	bst_destroy(&tree2);
	puts("--------------------");
}