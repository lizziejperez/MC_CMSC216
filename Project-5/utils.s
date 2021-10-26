; Utility functions for CMSC216
; Project #5 - Fall 2021
; Author: Sandro Fouche
; Copyright 2021


; Just a little main routine for testing purposes
;
;_MAIN
;			ADR		R0, HELLO
;			ADR		R1, TEST
;			BL		_CONCAT
;			BL		_STRLEN
;			END
;
; Two packed strings: "Hello, World!" and "This is a test."
;			
;HELLO		DCD		1819043144,1461726319,1684828783,33
;TEST		DCD		1936287828,544434464,1702109281,3044467

; Name: Elizabeth Perez
; Student ID: eperez57
; M-number: M20966722
_POST2INFIX
		STMFD	SP!, {R14,R11}
		MOV		R11, SP
		SUB		SP, SP, #16
		STR		R0, [R11, #-4] ; storing input string at FP-4
		BL		_STRLEN
		STR		R0, [R11, #-8] ; storing length of input string at FP-8
		MOV		R1, #0
		STR		R1, [R11, #-12] ; storing index counter at FP-12
_POST2INFIX_L1 ; checks if index < input.length
		LDR		R0, [R11, #-4] ; loads input string to R0
		LDR		R1, [R11, #-8] ; loads length of input string to R1
		LDR		R2, [R11, #-12] ; loads index counter to R2
		CMP		R2, R1
		BGE		_POST2INFIX_L6
_POST2INFIX_L2 ; gets the char, then increases index counter by 1
		LDRB		R1, [R0], #R2 ; loads char to R2
		ADD		R2, R2, #1
		STR		R2, [R11, #-12] ; updating index counter
_POST2INFIX_L3 ; if the charater is blank, skip it
		CMP		R1, #32
		BEQ		_POST2INFIX_L1
_POST2INFIX_L4 ; if the character is a digit, put in onto the stack
		CMP		R1, #48
		BLT		_POST2INFIX_L5
		CMP		R1, #57
		BGT		_POST2INFIX_L5
		; pushes the character onto the stack
		MOV		R0, R1
		BL		_PUSH
		B		_POST2INFIX_L1
_POST2INFIX_L5 ; it is an operator
		;	(a) pop the term2 off the stack
		BL		_POP
		;STR		R0, [R11 #-]
		;	(b) pop the term1 off the stack
		;	(c) concatenate: '('+term1+operator+term2+')'
		;	(d) push the concatenated string onto the stack
_POST2INFIX_L6 ; at the end of the input string, if there is only one thing on the stack, it is converted infix formulation of the expression
		BL		_STACK_SIZE
		CMP		R0, #1
		BNE		???
		BL		_POP

_POST2INFIX_RTN
		ADD		SP, SP, #16
		LDMFD	SP!, {R14,R11}
		MOVEQ	R15, R14

; ******* Subroutines begin here *******		

; returns the length of string passed into R0
; int _STRLEN(char *R0); pp
; clobbers registers: R0, R1, R2

_STRLEN
			MOV		R1, R0
_STRLEN_L1
			LDRB	R2, [R1], #1
			CMP		R2, #0
			BNE		_STRLEN_L1
_STRLEN_RET
			SUB		R0, R1, R0
			SUB		R0, R0, #1
			MOV		R15, R14
		
			
; allocates and returns a string that is the concatenation of strings passed into R0 & R1
; char *_CONCAT(char *R0, char *R1);	
; clobbers registers: R0, R1, R2, R3		

_CONCAT
			STMFD	SP!, {R14,R11}
			MOV		R11, SP
			SUB		SP, SP, #16
			STR		R0, [R11, #-8]
			STR		R1, [R11, #-12]
			BL		_STRLEN
			MOV		R3, R0
			LDR		R0, [R11, #-12]
			BL		_STRLEN
			ADD		R0, R0, R3
			ADD		R0, R0, #1
			BL		_ALLOC
			STR		R0, [R11, #-16]
			LDR		R1, [R11, #-8]
_CONCAT_1
			LDRB	R2, [R1], #1
			STRB	R2, [R0], #1
			CMP		R2, #0
			BNE		_CONCAT_1
			SUB		R0, R0, #1
			LDR		R1,[R11,#-12]
_CONCAT_2
			LDRB	R2, [R1], #1
			STRB	R2, [R0], #1
			CMP		R2, #0
			BNE		_CONCAT_2
			LDR		R0, [R11, #-16]
			ADD		SP, SP, #16
			LDMFD	SP!, {R14,R11}
			MOVEQ	R15, R14			


; Storage for the first available non-allocated memory address
_FREE_PTR	DCD		0x40000000


; If possible, allocates R0 bytes from free memory.  Returns the pointer or NULL. 	
; void *_ALLOC(unsigned long R0);
; clobbers registers: R0, R1, R2

_ALLOC
			ADR		R2, _FREE_PTR
			LDR		R1, [R2]
			ADD		R1, R1, R0
			MOV		R0, #0
			CMP		R1, #0xEE000000
			LDRLO	R0, [R2]
			STRLO	R1, [R2]
			MOV		R15, R14			


; Storage for a static application stack
_STACK		DCD		0xEF000000


; Returns the number of items stored on the application stack
; int _STACK_SIZE(); 
; clobbers registers: R0, R1

_STACK_SIZE
			ADR		R1, _STACK
			LDR		R0, [R1]
			MOV		R1, #0xEF000000
			SUB		R0, R1, R0
			ASR		R0, R0, #2
			MOV		R15, R14


; Adds R0 to the top of the application stack
; void _PUSH(char *R0); 
; clobbers registers: R1, R2

_PUSH
			ADR		R2, _STACK
			LDR		R1, [R2]
			STMFD	R1!, {R0}
			STR		R1, [R2]
			MOV		R15, R14


; Removes and returns the string at the top of the application stack via R0.
; char *_POP(); 
; clobbers registers: R0, R1, R2

_POP
			STMFD	SP!, {R14}
			BL		_PEEK
			ADDNE	R1, R1, #4
			LDMFD	SP!, {R14}
			STR		R1, [R2]
			MOV		R15, R14


; Returns the string at the top of the application stack via R0, without modifying the stack.				
; char *_PEEK(); 		
; clobbers registers: R0, R1, R2
		
_PEEK
			MOV		R0, #0
			ADR		R2, _STACK
			LDR		R1, [R2]
			CMP		R1, #0xEF000000
			MOVEQ	R15, R14
			LDMFD	R1, {R0}
			MOV		R15, R14
			
						

			
			
			
