# Project: Assembly Language II
## Overview
Write an assembly language program that accesses and makes use of C-subroutines.
### Objectives
- Understand Assembly language code
- Interfacing C and Assembly code
## Description
### What to do
Implement a simple postfix to infix expression converter.
Your assembly language program should assume a string address is passed in via R0 as a packed C-style string.
Then run the simplified postfix to infix algorithm specified below, and return a new string in infix notation via R0.
Your code should call the following C-style functions, as necessary:
```
// returns the length of string s
int _STRLEN(char *s);

// allocates and returns a string that is the concatenation of strings s1 and s2.
char *_CONCAT(char *s1, char *s2);

// If possible, allocates bytes from the heap. This is an all-or-nothing attempt
void *_ALLOC(unsigned long bytes);

// returns the number of items stored in stack
int _STACK_SIZE();

// adds s to the top of the stack.
void _PUSH(char *s);

// removes and returns the string at the top of the stack.
char *_POP();

// returns the string at the top of the stack, without modifying the stack.
char *_PEEK();
```
### Postfix to Infix Algorithm
Process each character of the input as follows:
1. If the character is blank, skip it.
2. If the character is a digit, put it onto the stack.
3. Otherwise, it is an operator.
   * Pop the term2 off the stack
   * Pop the term1 off the stack
   * Concatenate: '(' + term1 + operator + term2 + ')'
   * Push the concatenated string onto the stack
4. At the end of the input string, if there is only one thing on the stack, it is converted.
## Running the code
Use VisUAL ARM emulator to test the code. You can download VisUAL at: https://salmanarif.bitbucket.io/visual/downloads.html
