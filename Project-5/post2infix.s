; Name: Elizabeth Perez
; Student ID: eperez57
; M-number: M20966722
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
