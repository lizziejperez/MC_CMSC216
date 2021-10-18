#include "stack.h"
#define MAX_STR_LEN 100

void * allocate(unsigned long bytes) {
	static void *free_mem_ptr = (void *)0x800;
	const void *MAX_MEM_ADDR = (void *)0x1800;
	
	if (free_mem_ptr+bytes <= MAX_MEM_ADDR) {
		free_mem_ptr += bytes;
		return free_mem_ptr - bytes;
	}

	return 0;
}



int main() {
	
	char *s1 = "hello";			// assume that s1 is in R3
	int len1 = 5;				// assume that len1 is in R2
	char *s2 = "goodbye";		// assume that s2 is in R1
	int len2 = 7;				// assume that s2 is in R0
	
	char *result = allocate(len1 + len2 + 1);
	
	int i = 0;
	while(*s1) 
		result[i++] = *s1++;

	while(*s2) 
		result[i++] = *s2++;
	
	return result;				// "return" result in R0;
}
