main
		;		setup
		str		r11, [r13, #-4]!
		sub		r13, r13, #-20
		
		mov		r3, #5
		mov		r4, #43
		mov		r5, #0
		str		r5, [r13, #-4]
		str		r5, [r13, #-8]
		str		r5, [r13, #-12]
		str		r5, [r13, #-16]
		str		r5, [r13, #-20]
		;		dollars
		str		r3, [r13, #-4]
		mov		r3, #0
		;		quarters
		mov		r5, #25
		bl		DIVIDE
		str		r6, [r13, #-8]
		;		dimes
		mov		r5, #10
		bl		DIVIDE
		str		r6, [r13, #-12]
		;		nickels
		mov		r5, #5
		bl		DIVIDE
		str		r6, [r13, #-16]
		;		pennies
		str		r4, [r13, #-20]
		
		;		clean up
		add		r13, r13, #20
		ldr		r11, [r13, #4]
		END
		
DIVIDE
		mov		r6, #0
		mov		r7, #1
DIV1
		cmp		r4, r5
		blt		RTN
		add		r6, r6, r7
		sub		r4, r4, r5
		B		DIV1
RTN
		mov		r5, r6
		mov		PC, LR
