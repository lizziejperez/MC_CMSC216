; Name: Elizabeth Perez
; Student ID: eperez57
; M-number: M20966722

; Note: input is the address of a packed C-style string (reverse?)
; only use r0-r3, if others need use store/restore them using the stack
; if the charater(r4) is blank, skip it
		; if the character is a digit, put in onto the stack
		; otherwise, it is an operator
		;	(a) pop the term2 off the stack
		;	(b) pop the term1 off the stack
		;	(c) concatenate: '('+term1+operator+term2+')'
		;	(d) push the concatenated string onto the stack
		; at the end of the input string, if there is only one thing on the stack, it is converted infix formulation of the expression
_POST2INFIX
		; setup FP(R11) and SP(R13)
		STR		R11, [R13, #-4]!
		MOV		R11, R13
		SUB		R13, R13, #20
		
		STR		LR, [R11, #-8] ; storing LR at FP-8
		STR		R0, [R11, #-12] ; storing input string at FP-12
		BL		_STRLEN
		STR		R0, [R11, #-16] ; storing length of input string at FP-16
		MOV		R1, #0
		STR		R1, [R11, #-20] ; storing index counter at FP-20
_POST2INFIX_L1 ; checks if index < input.length
		LDR		R0, [R11, #-12] ; loads input string to R0
		LDR		R1, [R11, #-20] ; loads index counter to R1
		LDR		R2, [R11, #-16] ; loads length of input string to R2
		CMP		R1, R2
		BGE		_POST2INFIX_L6
_POST2INFIX_L2 ; gets the char, then increases index counter by 1
		LDRB		R2, [R0], #R1 ; loads char to R2
		ADD		R1, R1, #1
		STR		R1, [R11, #-20] ; updating index counter
_POST2INFIX_L3 ; if the charater is blank, skip it
		CMP		R2, #32
		BEQ		_POST2INFIX_L1
_POST2INFIX_L4 ; if the character is a digit, put in onto the stack
		CMP		R2, #48
		BLT		_POST2INFIX_L5
		CMP		R2, #57
		BGT		_POST2INFIX_L5
		; pushes the character onto the stack
		MOV		R0, R2
		BL		_PUSH
		B		_POST2INFIX_L1
_POST2INFIX_L5 ; it is an operator
		;	(a) pop the term2 off the stack
		;	(b) pop the term1 off the stack
		;	(c) concatenate: '('+term1+operator+term2+')'
		;	(d) push the concatenated string onto the stack
_POST2INFIX_L6 ; at the end of the input string, if there is only one thing on the stack, it is converted infix formulation of the expression

_POST2INFIX_RTN
		LDR		LR, [11, #-8] ; restoring LR from FP-8
		; restore FP and SP
		LDR		r11, [r13, #4]!
		ADD		r13, r13, #20