#include "bst.h"

int main() {

	bst tree;
	
	bst_create( &tree );
	bst_insert( &tree, "Hello, world" );
	bst_destroy( &tree );

}