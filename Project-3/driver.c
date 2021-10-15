#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

#define MAX 20

void test1();
void test2();
void test3();
void test4();
void test5();
void setup(bst *tree, bst *tree2);
void printInorder(bst *tree);

int main() {
	bst tree, tree2;
	setup(&tree, &tree2);
	printInorder(&tree);
	printInorder(&tree2);

	test1();
	test2();
	test3();
	test4();
	test5();

	return 0;
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

	/*          ___M(x4)___
	*          /           \
	*      ___E___         _V_
	*     /        \       /   \
	*   _C_         I     Q     X
	*  /   \       / \   / \   / \
	* A(x2) D(x3) G   K O   S W   Z
	*/
	bst_create(tree2);
	bst_insert(tree2, "M");
	bst_insert(tree2, "E");
	bst_insert(tree2, "C");
	bst_insert(tree2, "A");
	bst_insert(tree2, "D");
	bst_insert(tree2, "I");
	bst_insert(tree2, "G");
	bst_insert(tree2, "K");
	bst_insert(tree2, "V");
	bst_insert(tree2, "X");
	bst_insert(tree2, "Z");
	bst_insert(tree2, "W");
	bst_insert(tree2, "Q");
	bst_insert(tree2, "S");
	bst_insert(tree2, "O");
	bst_insert(tree2, "M");
	bst_insert(tree2, "M");
	bst_insert(tree2, "M");
	bst_insert(tree2, "A");
	bst_insert(tree2, "D");
	bst_insert(tree2, "D");
}

void printInorder(bst *tree) {
	char *dst;
	dst = malloc(sizeof(char)*MAX);
	bst_first(tree, dst);
	printf("%s", dst);
	int count = 1;
	while(count<tree->count) {
		bst_next(tree, dst);
		printf("%s", dst);
		count++;
	}
	printf("\n");
	bst_last(tree, dst);
	printf("%s", dst);
	count = 1;
	while(count<tree->count) {
		bst_previous(tree, dst);
		printf("%s", dst);
		count++;
	}
	printf("\n");
}

void test1() {
	bst tree;
	int status;
	puts("TEST 1: create, insert, destroy");

	status = bst_create(&tree);
	if(status!=BST_SUCCESS) printf("(Tree 1) create: %d error\n", status);

	status = bst_insert(&tree, "Howdy!");
	if(status!=BST_SUCCESS) printf("(Tree 1) insert - head case: %d error\n", status);
	status = bst_insert(&tree, "What's up?");
	if(status!=BST_SUCCESS) printf("(Tree 1) insert - normal case: s1 %d error\n", status);
	status = bst_insert(&tree, "Game on.");
	if(status!=BST_SUCCESS) printf("(Tree 1) insert - normal case: s2 %d error\n", status);
	status = bst_insert(&tree, "No way..");
	if(status!=BST_SUCCESS) printf("(Tree 1) insert - normal case: s3 %d error\n", status);
	status = bst_insert(&tree, "I don't know.");
	if(status!=BST_SUCCESS) printf("(Tree 1) insert - normal case: s4 %d error\n", status);
	
	status = bst_insert(&tree, "Howdy!");
	if(status!=BST_SUCCESS) printf("(Tree 1) insert - duplicate case: %d error", status);

	status = bst_destroy(&tree);
	if(status!=BST_SUCCESS) printf("(Tree 1) destroy: %d error", status);

	puts("--------------------");
}

void test2() {
	bst tree, tree2;
	int status;
	char *dst = malloc(sizeof(char)*MAX);
	puts("TEST 2: first, last");
	setup(&tree, &tree2);

	status = bst_first(&tree, dst);
	if(status!=BST_SUCCESS)
		printf("(Tree 1) first: %d error\n", status);
	else
		printf("(Tree 1) first: result[%s] expected[Game on.]\n", dst);
	status = bst_first(&tree2, dst);
	if(status!=BST_SUCCESS)
		printf("(Tree 2) first: %d error\n", status);
	else
		printf("(Tree 2) first: result[%s] expected[A]\n", dst);

	status = bst_last(&tree, dst);
	if(status!=BST_SUCCESS)
		printf("(Tree 1) last: %d error\n", status);
	else
		printf("(Tree 1) last: result[%s] expected[What's up?]\n", dst);
	status = bst_last(&tree2, dst);
	if(status!=BST_SUCCESS)
		printf("(Tree 2) last: %d error\n", status);
	else
		printf("(Tree 2) last: result[%s] expected[Z]\n", dst);

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

	value = "N/A";
	status = bst_find(&tree, value);
	if(status!=BST_ERR_NOT_FOUND) printf("(Tree 1) find - DNE case: %d error\n", status);
	status = bst_find(&tree2, value);
	if(status!=BST_ERR_NOT_FOUND) printf("(Tree 2) find - DNE case: %d error\n", status);

	value = "What's up?";
	status = bst_find(&tree, value);
	if(status!=BST_SUCCESS) printf("(Tree 1) find - normal case: %d error\n", status);
	value = "Game on.";
	status = bst_find(&tree, value);
	if(status!=BST_SUCCESS) printf("(Tree 1) find - normal case: %d error\n", status);
	value = "D";
	status = bst_find(&tree2, value);
	if(status!=BST_SUCCESS) printf("(Tree 2) find - normal case: %d error\n", status);
	value = "Z";
	status = bst_find(&tree2, value);
	if(status!=BST_SUCCESS) printf("(Tree 2) find - normal case: %d error\n", status);

	bst_destroy(&tree);
	bst_destroy(&tree2);
	puts("--------------------");
}

void test4() {
	bst tree, tree2;
	int status;
	char *dst, *value, *value2;
	puts("TEST 4: next, previous");
	setup(&tree, &tree2);
	dst = malloc(sizeof(char)*MAX);

	status = bst_next(&tree, dst);
	if(status!=BST_ERR_NULL_POINTER) printf("(Tree 1) next - no curr: %d error\n", status);
	if(status==BST_SUCCESS) printf("result[%s]\n", dst);
	status = bst_next(&tree2, dst);
	if(status!=BST_ERR_NULL_POINTER) printf("(Tree 2) next - no curr: %d error\n", status);
	if(status==BST_SUCCESS) printf("result[%s]\n", dst);

	status = bst_previous(&tree, dst);
	if(status!=BST_ERR_NULL_POINTER) printf("(Tree 1) previous - no curr: %d error\n", status);
	if(status==BST_SUCCESS) printf("result[%s]\n", dst);
	status = bst_previous(&tree2, dst);
	if(status!=BST_ERR_NULL_POINTER) printf("(Tree 2) previous - no curr: %d error\n", status);
	if(status==BST_SUCCESS) printf("result[%s]\n", dst);

	value = "Howdy!";
	value2 = "I";

	bst_find(&tree, value);
	status = bst_next(&tree, dst);
	if(status!=BST_SUCCESS)
		printf("(Tree 1) next - normal case: %d error\n", status);
	else
		printf("(Tree 1) next - normal case: result[%s] expected[Howdy!]\n", dst);
	status = bst_next(&tree, dst);
	if(status!=BST_SUCCESS)
		printf("(Tree 1) next - normal case: %d error\n", status);
	else
		printf("(Tree 1) next - normal case: result[%s] expected[I don't know.]\n", dst);
	bst_find(&tree2, value2);
	status = bst_next(&tree2, dst);
	if(status!=BST_SUCCESS)
		printf("(Tree 2) next - normal case: %d error\n", status);
	else
		printf("(Tree 2) next - normal case: result[%s] expected[K]\n", dst);

	bst_find(&tree, value);
	status = bst_previous(&tree, dst);
	if(status!=BST_SUCCESS)
		printf("(Tree 1) previous - normal case: %d error\n", status);
	else
		printf("(Tree 1) previous - normal case: result[%s] expected[Game on.]\n", dst);
	bst_find(&tree2, value2);
	status = bst_previous(&tree2, dst);
	if(status!=BST_SUCCESS)
		printf("(Tree 2) previous - normal case: %d error\n", status);
	else
		printf("(Tree 2) previous - normal case: result[%s] expected[G]\n", dst);

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
	printf("(Tree 1):\n");
	printInorder(&tree);
	printf("(Tree 2):\n");
	printInorder(&tree2);

	value = "Game on."; /*no children*/
	printf("(Tree 1) removing[%s]\n", value);
	status = bst_remove(&tree, value);
	if(status!=BST_SUCCESS) printf("(Tree 1) remove - normal case: %d error", status);
	value = "No way.."; /*one child*/
	printf("(Tree 1) removing[%s]\n", value);
	status = bst_remove(&tree, value);
	if(status!=BST_SUCCESS) printf("(Tree 1) remove - normal case: %d error", status);
	printInorder(&tree);
	value = "C"; /*2 children*/
	printf("(Tree 2) removing[%s]\n", value);
	status = bst_remove(&tree2, value);
	if(status!=BST_SUCCESS) printf("(Tree 2) remove - normal case: %d error", status);
	value = "V"; /*2 children*/
	printf("(Tree 2) removing[%s]\n", value);
	status = bst_remove(&tree2, value);
	if(status!=BST_SUCCESS) printf("(Tree 2) remove - normal case: %d error", status);
	printInorder(&tree2);

	value = "Nothing";
	printf("(Tree 1) removing[%s]\n", value);
	status = bst_remove(&tree, value);
	if(status!=BST_ERR_NOT_FOUND) printf("(Tree 1) remove - DNE case: %d error", status);
	printInorder(&tree);
	printf("(Tree 2) removing[%s]\n", value);
	status = bst_remove(&tree2, value);
	if(status!=BST_ERR_NOT_FOUND) printf("(Tree 2) remove - DNE case: %d error", status);
	printInorder(&tree2);

	value = "Howdy!";
	printf("(Tree 1) removing[%s]\n", value);
	status = bst_remove(&tree, value);
	if(status!=BST_SUCCESS) printf("(Tree 1) remove - dupl case: %d error", status);
	printInorder(&tree);
	printf("(Tree 1) removing[%s]\n", value);
	status = bst_remove(&tree, value);
	if(status!=BST_SUCCESS) printf("(Tree 1) remove - dupl case: %d error", status);
	status = bst_remove(&tree, value);
	if(status==BST_SUCCESS) puts("(Tree 1) remove - dupl case: Unexpected success");
	printInorder(&tree);
	value = "D";
	printf("(Tree 2) removing[%s]\n", value);
	status = bst_remove(&tree2, value);
	if(status!=BST_SUCCESS) printf("(Tree 2) remove - dupl case: %d error", status);
	printInorder(&tree2);
	printf("(Tree 2) removing[%s]\n", value);
	status = bst_remove(&tree2, value);
	if(status!=BST_SUCCESS) printf("(Tree 2) remove - dupl case: %d error", status);
	printf("(Tree 2) removing[%s]\n", value);
	status = bst_remove(&tree2, value);
	if(status!=BST_SUCCESS) printf("(Tree 2) remove - dupl case: %d error", status);
	status = bst_remove(&tree2, value);
	if(status==BST_SUCCESS) puts("(Tree 2) remove - dupl case: Unexpected success");
	printInorder(&tree2);

	bst_destroy(&tree);
	bst_destroy(&tree2);
	puts("--------------------");
}