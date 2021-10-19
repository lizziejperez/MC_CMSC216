main
		str		r11, [r13, #-4]!
		add		r11, r13, #0
		mov		r3, #5
		mov		r4, #43
		mov		r5, #0
		str		r5, [r13, #-4]
		str		r5, [r13, #-8]
		str		r5, [r13, #-12]
		str		r5, [r13, #-16]
		str		r5, [r13, #-20]
		;		DOLLARS
		str		r3, [r13, #-4]
		mov		r3, #0
		;		QUARTERS
		mov		r5, #25
		bl		DIVIDE
		str		r6, [r13, #-8]
		;		DIMES
		mov		r5, #10
		bl		DIVIDE
		str		r6, [r13, #-12]
		;		NICKELS
		mov		r5, #5
		bl		DIVIDE
		str		r6, [r13, #-16]
		;		PENNIES
		str		r4, [r13, #-20]
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
