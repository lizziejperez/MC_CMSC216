#include "bst.h"

int main() {

	bst tree;
	char *welcome = "Hello, world";
	char *goodbye = "That's all folks!";
	
	bst_create( &tree );
	bst_insert( &tree, welcome );
	bst_insert( &tree, goodbye );
	bst_remove( &tree, welcome );
	bst_destroy( &tree );
	
}