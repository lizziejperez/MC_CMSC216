; Name: Elizabeth Perez
; Student ID: eperez57
; M-number: M20966722

_MAIN
			;ADR		R0, GFA_THREE
			;BL		_POST2INFIX
			;MOV		R6, R0
			ADR		R0, TEST_FOUR
			BL		_POST2INFIX
			MOV		R6, R0
			END
; Test Packed Strings
;GFA_ONE		DCD		540155953,540221483,42
;GFA_TWO		DCD		540352564,539631670,43
;GFA_THREE		DCD		540549175,539697209,42
;TEST_ONE		DCD		540155953,540221485,47
;TEST_TWO		DCD		540352564,539959350,45
;TEST_THREE		DCD		540549175,539828281,47
TEST_FOUR		DCD		540155953,540221483,540287018,540418101,539697194,540483629,540614712,5
;TEST_FIVE		DCD		540155953,540024875,42

_POST2INFIX
		STMFD	SP!, {R14,R11}
		MOV		R11, SP
		SUB		SP, SP, #24
		STR		R0, [R11, #-4] ; storing input at FP-4
		MOV		R0, #0
		STR		R0, [R11, #-8] ; storing index counter at FP-8
_POST2INFIX_L1
		LDR		R0, [R11, #-4] ; loads input string to R0
		LDR		R1, [R11, #-8] ; loads index to R1
		LDRB		R2, [R0, R1] ; loads the character (input[index]) to R2
		CMP		R2, #0
		BEQ		_POST2INFIX_RTN ; branches if the character is null
		CMP		R2, #32
		BEQ		_POST2INFIX_L4 ; branches if the character is blank
		STR		R2, [R11, #-12] ; stores the character at FP-12
		MOV		R0, #2
		BL		_ALLOC
		CMP		R0, #0
		BEQ		_POST2INFIX_ERR ; if _ALLOC fails, return error
		LDR		R2, [R11, #-12] ; loads the character to R2
		STRB		R2, [R0] ; stores the character in char*
		CMP		R2, #48
		BLT		_POST2INFIX_L2 ; branches if the character is less than '0'
		CMP		R2, #57
		BGT		_POST2INFIX_L2 ; branches if the character is less than '9'
		BL		_PUSH ; push the char* with the character (a digit) onto stack
		B		_POST2INFIX_L4
_POST2INFIX_L2
		STR		R0, [R11, #-12] ; storing the operator at FP-12
		LDR		R0, [R11, #-16]
		CMP		R0, #0
		BNE		_POST2INFIX_L3 ; branches if FP-16 is not 0
		MOV		R0, #2
		BL		_ALLOC
		CMP		R0, #0
		BEQ		_POST2INFIX_ERR ; if _ALLOC fails, return error
		MOV		R2, #40
		STRB		R2, [R0] ; stores '(' in char*
		STR		R0, [R11, #-16] ; storing "(" at FP-16
		MOV		R0, #2
		BL		_ALLOC
		CMP		R0, #0
		BEQ		_POST2INFIX_ERR ; if _ALLOC fails, return error
		MOV		R2, #41
		STRB		R2, [R0] ; stores ')' in char*
		STR		R0, [R11, #-20] ; storing ")" at FP-20
_POST2INFIX_L3
		BL		_POP ; pop the term2 off the stack
		STR		R0, [R11, #-24] ; storing term2 at FP-24
		BL		_POP ; pop the term1 off the stack
		MOV		R1, R0
		LDR		R0, [R11, #-16]
		BL		_CONCAT ; '('+term1
		LDR		R1, [R11, #-12]
		BL		_CONCAT ; '('+term1+operator
		LDR		R1, [R11, #-24]
		BL		_CONCAT ; '('+term1+operator+term2
		LDR		R1, [R11, #-20]
		BL		_CONCAT ; '('+term1+operator+term2+')'
		BL		_PUSH ; push the concatenated char* onto the stack
_POST2INFIX_L4
		LDR		R1, [R11, #-8] ; loads index to R1
		ADD		R1, R1, #1
		STR		R1, [R11, #-8] ; increases index by 1
		B		_POST2INFIX_L1 ; next loop iteration (checks the next character)
_POST2INFIX_ERR
		MOV		R0, #0
		B		_POST2INFIX_END
_POST2INFIX_RTN
		BL		_STACK_SIZE
		CMP		R0, #1
		BNE		_POST2INFIX_ERR ; if there is not one thing on the stack, return error
		BL		_POP
_POST2INFIX_END
		ADD		SP, SP, #24
		LDMFD	SP!, {R14,R11}
		MOV	R15, R14

; Utility functions for CMSC216
; Project #5 - Fall 2021
; Author: Sandro Fouche
; Copyright 2021
			
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