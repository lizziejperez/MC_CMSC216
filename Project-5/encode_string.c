/* encode_string.c
 
 	a small C program that asks for a label and a line of text, and encodes that text as a packed string ARM DCD instruction.

	by Sandro Fouche
	Copyright 2021
*/

#include <stdio.h>
#include <string.h>

#define STR_SZ		256
#define WORD_SIZE	4

int main() {

	char label[STR_SZ+1];
	char string[STR_SZ+3];
	int *str = (int *)string;

	printf("Input label name: ");
	scanf("%s", label);
	fgets(string,STR_SZ, stdin);

	printf("Input String to Encode: ");
	fgets(string, STR_SZ, stdin);
	bzero(string+strlen(string)-1,  3);
		
	for(int i=0; label[i]; i++)
		label[i] &= ~32;
	
	printf("%s DCD ", label);
	
	for(int i=0; i <= (strlen(string)-1)/WORD_SIZE; i++) 
			printf(i?",%d":"%d", *(str++));
	
	printf ("\n");

}