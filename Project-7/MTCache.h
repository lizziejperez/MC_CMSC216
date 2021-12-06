#ifndef _MTCACHE_H
#define _MTCACHE_H

// Typedef for MTCACHE structure.  Create a full definition in your MTCache.c file
typedef struct _mt_cache MTCache;

/*
 *	MTL_init()
 *	Allocate and initialize a Most Recently Used (MRU) cache structure with the specified size.
 */
MTCache *MTL_init(int);

/*
 *	MTL_add()
 *	Takes a cache pointer and integer value as parameters.
 *	Insert the specified value into the cache.
 *	If the cache is full, the least-recently-used (LRU) element should be removed and returned.
 *  If the value is already in the cache, simply make it the most recently used element (do not insert it again)
 *	Returns 0, if the cache insert succeeded and did not remove an LRU element.
 *	Returns the value, of the LRU element, if it was removed.
 *	Returns -1, if an attempt to insert value <= 0.
 */
int MTL_add(MTCache *, int);

/*
 *	MTL_update()
 *	Takes a cache pointer and integer value as parameters.
 *	Make the specified value the most recently used value in the cache.
 *	Returns 0 on success, -1 if the value is not in the cache.
 */
int MTL_update(MTCache *, int);

/*
 *	MTL_delete()
 *	Takes a cache pointer and integer value as parameters.
 *	Removes the specified value from the cache. 
 *	Returns 0 on success, -1 if the value is not in the cache.
 */
int MTL_delete(MTCache *, int);

/*
 *	MTL_size()
 *	Takes a cache pointer as a parameter.
 *	Returns the number of *used* elements in the cache.
 */
int MTL_size(MTCache *);

/*
 *	MTL_print()
 *	Takes a cache pointer as a parameter.
 *	Prints out the contents of the cache.
 *	The output should consist of a space-delimited list of integers ending with a newline.
 *	The output list the integers in order from most to least recently used.
 */
void MTH_print(MTCache *);

#endif /* _MTCACHE_H */