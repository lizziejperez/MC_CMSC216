; Name: Elizabeth Perez
; Student ID: eperez57
; M-number: M20966722

post2infix
		;		setup FP(r11) and SP(r13)
		str		r11, [r13, #-4]!
		mov		r11, r13
		;		storing LR at FP-8
		sub		r13, r13, #-8
		str		LR, [r11, #-8]
		;		storing input in r3
		mov		r3, r0
		;		Note: input is the address of a packed C-style string (reverse?)
		;		sets r2 to _STRLEN(r0)
		bl		_STRLEN
		mov     r2, r0
		;		starts processing the string
		bl		process0
		;		restoring LR from FP-8
		ldr		LR, [r11, #-8]
		add		r13, r13, #8
		;		restore FP and SP
		ldr		r11, [r13, #4]!

process0
		ldrb		r4, [r3, #r2]
		cmp		r4, #0
		bne		process1
		mov		PC, LR
process1
		;		if the charater(r4) is blank, skip it
		;		if the character is a digit, put in onto the stack
		;		otherwise, it is an operator
		;				(a) pop the term2 off the stack
		;				(b) pop the term1 off the stack
		;				(c) concatenate: '('+term1+operator+term2+')'
		;				(d) push the concatenated string onto the stack
		;		at the end of the input string, if there is only one thing on the stack, it is converted infix formulation of the expression