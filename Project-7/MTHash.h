#ifndef _MTHASH_H
#define _MTHASH_H

// Typedef for MTHash structure.  Create a full definition in your MTHash.c file
typedef struct _mt_hashtable MTHash;

/*
 *	MTH_init()
 *	Allocate and initialize a hash table structure with the specified table size.
 *	Each table entry should point to a linked list of data buckets.
 *	Set up one lock for each bucket . You should not use one lock for the whole hash table
 *	otherwise, hash performance will be pretty poor.
 *	Returns a pointer to the hash table.
 */
MTHash *MTH_init(int);

/*
 *	MTH_add()
 *	Takes a Hash Table pointer and integer value as parameters.
 *	Insert the specified value into the hash table. 
 *	Returns 0 on success, -1 if the value is already in the hash table (and does not add it again). 
 *	Note: The table entry that should be selected for a given value is: entry = value % table size.
 */
int MTH_add(MTHash *, int);

/*
 *	MTH_delete()
 *	Takes a Hash Table pointer and integer value as parameters.
 *	Removes the specified value from the hash table. 
 *	Returns 0 on success, -1 if the value is not in the hash table.
 */
int MTH_delete(MTHash *, int);

/*
 *	MTH_size()
 *	Takes a Hash Table pointer as a parameter.
 *	Returns the number of elements in the hash table.
 */
int MTH_size(MTHash *);

/*
 *	MTH_bucket_size()
 *	Takes a Hash Table pointer and table entry number as parameters.
 * 	Returns the number of elements in the specified table entry's bucket.
 */
int MTH_bucket_size(MTHash *, int);

/*
 *	MTH_print()
 *	Takes a Hash Table pointer as a parameter.
 *	Prints out the contents of the specified hash table.
 *	Print each bucket as a space-delimited list of integers on a single line
 *	Print a new line after each bucket.  Empty buckets should result in a blank line.
 */
void MTH_print(MTHash *);

#endif /* _MTHASH_H */