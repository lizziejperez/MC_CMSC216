main
		;		fp(r11-b) and sp(r13-t) setup
		str		r11, [r13, #-4]!
		;add		r11, r13, #0
		sub		r13, r13, #24
		str		LR, [fp, #-8
		;		vars setup
		mov		r3, #hello
		;ldrb	r5, [r3,#4] second letter
		mov		r2, #5
		mov		r1, #goodbye
		mov		r0, #7
		;		Result
		mov		r4, #0
		add		r4, r4, r2
		add		r4, r4, r0
		add		r4, r4, #1
		bl		ALLOC
		mov		r4, #0
		;		While loops
		;		fp and sp clean up
		add		sp, sp, #4
		ldr		fp, [sp]
		mov		LR, PC
		sub		r13, r11, #0
		ldr		r11, [r13, #4]
		end
		
ALLOC
		
hello	DCD		104, 101, 108, 108, 111, 0
goodbye	DCD		103, 111, 111, 100, 98, 121, 101, 0
