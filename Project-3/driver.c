#include <stdio.h>
#include "bst.h"

int main() {
	bst tree;
	int status;

/*TEST bst_create*/
	puts("Testing bst_create:");
	status = bst_create(&tree);
	if(status!=BST_SUCCESS) printf("%d error", status);
	if(tree.count!=0) puts("tree count wrong value");
	if(tree.head!=NULL) puts("tree head not null");
	if(tree.curr!=NULL) puts("tree curr not null");
	puts("End of test.");

/*TEST bst_insert*/
	puts("Testing bst_insert (1):");
	status = bst_insert(&tree, "Howdy!");
	if(status!=BST_SUCCESS) printf("%d error", status);
	puts("End of test.");

	/*puts("Testing bst_insert (2):");
	status = bst_insert(&tree, "What's up?");
	if(status!=BST_SUCCESS) printf("s1 %d error", status);
	status = bst_insert(&tree, "Game on.");
	if(status!=BST_SUCCESS) printf("s2 %d error", status);
	status = bst_insert(&tree, "No way..");
	if(status!=BST_SUCCESS) printf("s3 %d error", status);
	status = bst_insert(&tree, "I don't know.");
	if(status!=BST_SUCCESS) printf("s4 %d error", status);
	puts("End of test.");*/

	/*puts("Testing bst_insert (3):");
	status = bst_insert(&tree, "Howdy!");
	if(status!=BST_SUCCESS) printf("%d error", status);
	puts("End of test.");*/

/*TEST bst_destroy*/
	puts("Testing bst_destroy:");
	status = bst_destroy(&tree);
	if(status!=BST_SUCCESS) printf("%d error", status);
	puts("End of test.");

/*TEST bst_first*/
	/*puts("Testing bst_first:");
	status = bst_first(&tree);
	if(status!=BST_SUCCESS) printf("%d error", status);*/

/*TEST bst_next*/
	/*puts("Testing bst_next:");
	status = bst_next(&tree);
	if(status!=BST_SUCCESS) printf("%d error", status);*/

/*TEST bst_previous*/
	/*puts("Testing bst_previous:");
	status = bst_previous(&tree);
	if(status!=BST_SUCCESS) printf("%d error", status);*/

/*TEST bst_last*/
	/*puts("Testing bst_last:");
	status = bst_last(&tree);
	if(status!=BST_SUCCESS) printf("%d error", status);*/

/*TEST bst_find*/
	/*puts("Testing bst_find:");
	status = bst_find(&tree);
	if(status!=BST_SUCCESS) printf("%d error", status);*/

/*TEST bst_remove*/
	/*puts("Testing bst_remove:");
	status = bst_remove(&tree);
	if(status!=BST_SUCCESS) printf("%d error", status);*/
    return 0;
}