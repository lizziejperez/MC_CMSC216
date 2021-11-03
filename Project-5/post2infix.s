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

;************* CURRENT ********************
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
		MOV		R0, R2
		BL		_POST2INFIX_CHARPTR ; creates and returns a char* with the character in R0
		LDR		R2, [R11, #-12] ; loads the character to R2
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
		BNE		_POST2INFIX_L3
		MOV		R0, #40
		BL		_POST2INFIX_CHARPTR
		STR		R0, [R11, #-16] ; storing '(' at FP-16
		MOV		R0, #41
		BL		_POST2INFIX_CHARPTR
		STR		R0, [R11, #-20] ; storing ')' at FP-20
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
_POST2INFIX_CHARPTR
		STMFD	SP!, {R14,R11}
		MOV		R11, SP
		SUB		SP, SP, #4
		STR		R0, [R11, #-4]
		MOV		R0, #2
		BL		_ALLOC
		CMP		R0, #0
		BEQ		_POST2INFIX_ERR ; if _ALLOC fails, return error
		LDR		R1, [R11, #-4]
		STRB		R1, [R0]
		ADD		SP, SP, #4
		LDMFD	SP!, {R14,R11}
		MOV	R15, R14
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

; ********************************************************
_POST2INFIX ; setup
		STMFD	SP!, {R14,R11}
		MOV		R11, SP
		SUB		SP, SP, #24
		STR		R0, [R11, #-4] ; storing input (a string address) at FP-4
		MOV		R0, #0
		STR		R0, [R11, #-8] ; storing index counter at FP-8
		STR		R0, [R11, #-12] ; storing 0 at FP-12
		STR		R0, [R11, #-16] ; storing 0 at FP-16
_POST2INFIX_L1
		LDR		R0, [R11, #-4] ; loads input string to R0
		LDR		R1, [R11, #-8] ; loads index counter to R1
		LDRB		R2, [R0, R1] ; loads the charater (input[index]) to R2
		CMP		R2, #0
		BEQ		_POST2INFIX_RTN ; if the charater is null, branch to _POST2INFIX_RTN
		CMP		R2, #32
		BEQ		_POST2INFIX_L4 ; if the charater is blank, branch to _POST2INFIX_L4
		; allocate space in memory for the character 
		STR		R2, [R11, #-12] ; stores the character at FP-12
		MOV		R0, #2
		BL		_ALLOC
		CMP		R0, #0
		BEQ		_POST2INFIX_ERR ; if _ALLOC(4) fails, branch to _POST2INFIX_ERR
		LDR		R2, [R11, #-12] ; restores the character to R2
		STRB		R2, [R0]
		; if the character is less than '0', branch to _POST2INFIX_L2
		CMP		R2, #48
		BLT		_POST2INFIX_L2
		; if the character is less than '9', branch to _POST2INFIX_L2
		CMP		R2, #57
		BGT		_POST2INFIX_L2
		; the charater is a digit - push onto stack
		BL		_PUSH
		B		_POST2INFIX_L4
_POST2INFIX_L2 ; it is an operator
		STR		R0, [R11, #-12] ; storing the operator at FP-12
		LDR		R0, [R11, #-16]
		CMP		R0, #0
		BNE		_POST2INFIX_L3
		; allocate space in memory for '('
		MOV		R0, #2
		BL		_ALLOC
		CMP		R0, #0
		BEQ		_POST2INFIX_ERR ; if _ALLOC(4) fails, branch to _POST2INFIX_ERR
		MOV		R1, #40
		STRB		R1, [R0]
		STR		R0, [R11, #-16] ; storing '(' at FP-16
		; allocate space in memory for ')'
		MOV		R0, #2
		BL		_ALLOC
		CMP		R0, #0
		BEQ		_POST2INFIX_ERR ; if _ALLOC(4) fails, branch to _POST2INFIX_ERR
		MOV		R1, #41
		STRB		R1, [R0]
		STR		R0, [R11, #-20] ; storing ')' at FP-20
_POST2INFIX_L3
		BL		_POP ; (a) pop the term2 off the stack
		STR		R0, [R11, #-24] ; storing term2 at FP-24
		BL		_POP ; (b) pop the term1 off the stack
		; (c) concatenate: '('+term1+operator+term2+')'
		MOV		R1, R0
		LDR		R0, [R11, #-16]
		BL		_CONCAT ; '('+term1
		LDR		R1, [R11, #-12]
		BL		_CONCAT ; '('+term1+operator
		LDR		R1, [R11, #-24]
		BL		_CONCAT ; '('+term1+operator+term2
		LDR		R1, [R11, #-20]
		BL		_CONCAT ; '('+term1+operator+term2+')'
		BL		_PUSH ; (d) push the concatenated string onto the stack
_POST2INFIX_L4
		; increases index counter by 1
		LDR		R1, [R11, #-8] ; loads index counter to R1
		ADD		R1, R1, #1
		STR		R1, [R11, #-8]
		B		_POST2INFIX_L1
_POST2INFIX_RTN ; at the end of the input string, if there is only one thing on the stack, it is converted infix formulation of the expression
		BL		_STACK_SIZE
		CMP		R0, #1
		BNE		_POST2INFIX_ERR
		BL		_POP
		B		_POST2INFIX_END
_POST2INFIX_ERR
		MOV		R0, #-1
		B		_POST2INFIX_END
_POST2INFIX_END ; clean up
		ADD		SP, SP, #24
		LDMFD	SP!, {R14,R11}
		MOV	R15, R14

; ********* OLD CODE VERSIONS ***********************
_POST2INFIX ; setup
		STMFD	SP!, {R14,R11}
		MOV		R11, SP
		SUB		SP, SP, #28
		STR		LR, [R11, #-8] ; storing LR at FP-8
		STR		R0, [R11, #-12] ; storing input (a string address) at FP-12
		MOV		R0, #0
		STR		R0, [R11, #-16] ; storing index counter at FP-16
		STR		R0, [R11, #-20] ; storing 0 at FP-20
		STR		R0, [R11, #-24] ; storing 0 at FP-24
_POST2INFIX_L1
		LDR		R0, [R11, #-12] ; loads input string to R0
		LDR		R1, [R11, #-16] ; loads index counter to R1
		LDRB		R2, [R0, R1] ; loads the charater (input[index]) to R2
		CMP		R2, #0
		BEQ		_POST2INFIX_RTN ; if the charater is null, branch to _POST2INFIX_RTN
		CMP		R2, #32
		BEQ		_POST2INFIX_L4 ; if the charater is blank, branch to _POST2INFIX_L4
		; allocate space in memory for the character 
		STR		R2, [R11, #-20] ; stores the character at FP-20
		MOV		R0, #4
		BL		_ALLOC
		CMP		R0, #0
		BEQ		_POST2INFIX_ERR ; if _ALLOC(4) fails, branch to _POST2INFIX_ERR
		LDR		R2, [R11, #-20] ; restores the character to R2
		STRB		R2, [R0]
		; if the character is less than '0', branch to _POST2INFIX_L2
		CMP		R2, #48
		BLT		_POST2INFIX_L2
		; if the character is less than '9', branch to _POST2INFIX_L2
		CMP		R2, #57
		BGT		_POST2INFIX_L2
		; the charater is a digit - push onto stack
		BL		_PUSH
		B		_POST2INFIX_L4
_POST2INFIX_L2 ; it is an operator
		STR		R0, [R11, #-20] ; storing the operator at FP-20
		LDR		R0, [R11, #-24]
		CMP		R0, #0
		BNE		_POST2INFIX_L3
		; allocate space in memory for '('
		MOV		R0, #4
		BL		_ALLOC
		CMP		R0, #0
		BEQ		_POST2INFIX_ERR ; if _ALLOC(4) fails, branch to _POST2INFIX_ERR
		MOV		R1, #40
		STRB		R1, [R0]
		STR		R0, [R11, #-24] ; storing '(' at FP-24
		; allocate space in memory for ')'
		MOV		R0, #4
		BL		_ALLOC
		CMP		R0, #0
		BEQ		_POST2INFIX_ERR ; if _ALLOC(4) fails, branch to _POST2INFIX_ERR
		MOV		R1, #40
		STRB		R1, [R0]
		STR		R0, [R11, #-28] ; storing ')' at FP-28
_POST2INFIX_L3
		SUB		SP, SP, #4
		BL		_POP ; (a) pop the term2 off the stack
		STR		R0, [R11, #-32] ; storing term2 at FP-32
		BL		_POP ; (b) pop the term1 off the stack
		; (c) concatenate: '('+term1+operator+term2+')'
		MOV		R1, R0
		LDR		R0, [R11, #-24]
		BL		_CONCAT ; '('+term1
		LDR		R1, [R11, #-20]
		BL		_CONCAT ; '('+term1+operator
		LDR		R1, [R11, #-32]
		BL		_CONCAT ; '('+term1+operator+term2
		LDR		R1, [R11, #-28]
		BL		_CONCAT ; '('+term1+operator+term2+')'
		BL		_PUSH ; (d) push the concatenated string onto the stack
		ADD		SP, SP, #4
_POST2INFIX_L4
		; increases index counter by 1
		LDR		R1, [R11, #-16] ; loads index counter to R1
		ADD		R1, R1, #1
		STR		R1, [R11, #-16]
		B		_POST2INFIX_L1
_POST2INFIX_ERR
		MOV		R0, #-1
		B		_POST2INFIX_END
_POST2INFIX_RTN ; at the end of the input string, if there is only one thing on the stack, it is converted infix formulation of the expression
		BL		_STACK_SIZE
		CMP		R0, #1
		BNE		_POST2INFIX_ERR
		BL		_POP
_POST2INFIX_END ; clean up
		LDR		LR, [11, #-8] ; restoring LR from FP-8
		ADD		SP, SP, #28
		LDMFD	SP!, {R14,R11}
		MOVEQ	R15, R14
;*****************************************************
;_POST2INFIX
		; setup FP(R11) and SP(R13)
		;STR		R11, [R13, #-4]!
		;MOV		R11, R13
		;SUB		R13, R13, #20
		;STR		LR, [R11, #-8] ; storing LR at FP-8
		;STR		R0, [R11, #-12] ; storing input string at FP-12
		;BL		_STRLEN
		;STR		R0, [R11, #-16] ; storing length of input string at FP-16
		;MOV		R1, #0
		;STR		R1, [R11, #-20] ; storing index counter at FP-20
;_POST2INFIX_L1 ; checks if index < input.length
		;LDR		R0, [R11, #-12] ; loads input string to R0
		;LDR		R1, [R11, #-20] ; loads index counter to R1
		;LDR		R2, [R11, #-16] ; loads length of input string to R2
		;CMP		R1, R2
		;BGE		_POST2INFIX_L6
;_POST2INFIX_L2 ; gets the char, then increases index counter by 1
		;LDRB		R2, [R0], #R1 ; loads char to R2
		;ADD		R1, R1, #1
		;STR		R1, [R11, #-20] ; updating index counter
;_POST2INFIX_L3 ; if the charater is blank, skip it
		;CMP		R2, #32
		;BEQ		_POST2INFIX_L1
;_POST2INFIX_L4 ; if the character is a digit, put in onto the stack
		;CMP		R2, #48
		;BLT		_POST2INFIX_L5
		;CMP		R2, #57
		;BGT		_POST2INFIX_L5
		; pushes the character onto the stack
		;MOV		R0, R2
		;BL		_PUSH
		;B		_POST2INFIX_L1
;_POST2INFIX_L5 ; it is an operator
		;	(a) pop the term2 off the stack
		;	(b) pop the term1 off the stack
		;	(c) concatenate: '('+term1+operator+term2+')'
		;	(d) push the concatenated string onto the stack
;_POST2INFIX_L6 ; at the end of the input string, if there is only one thing on the stack, it is converted infix formulation of the expression
;_POST2INFIX_RTN
		;LDR		LR, [11, #-8] ; restoring LR from FP-8
		; restore FP and SP
		;LDR		r11, [r13, #4]!
		;ADD		r13, r13, #20