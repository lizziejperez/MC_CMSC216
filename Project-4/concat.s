main
		;		setup
		;str		r11, [r13, #-4]!
		mov		r11, #0x0A000000
		mov		r13, r11
		sub		r13, r13, #-8
		str		LR, [r11, #-8]
		
		mov		r3, #hello
		mov		r2, #5
		mov		r1, #goodbye
		mov		r0, #7
		
		sub		r13, r13, #-4
		str		r0, [r11, #-12]
		add		r0, r0, r2
		add		r0, r0, #1
		bl		_allocate
		ldr		r0, [r11, #-12]
		add		r13, r13, #4
		
		mov		r4, #0
		mov		r5, #-8
		cmp		r3, #0
		blne		whileS1
		mov		r4, #0
		cmp		r1, #0
		blne		whileS2
		
		mov		r0, r11
		sub		r0, r0, #8
		
		;		clean up
		ldr		LR, [r11, #-8]
		add		r13, r13, #8
		end
		
_allocate
		sub		r13, r13, r0
		mov		PC, LR
		
whileS1
		;		goes thru each character in s1 (r3) and adds it into result at index i (r?)
		;		the index i and s1 are incrementing each iteration
		;		note: ldrb	r5, [r3,#4] second letter
		ldrb		r6, [r3, r4]
		str		r6, [r11, r5]
		add		r4, r4, #4
		add		r5, r5, #-4
		ldrb		r6, [r3, r4]
		cmp		r6, #0
		bne		whileS1
		mov		PC, LR
		
whileS2
		ldrb		r6, [r1, r4]
		str		r6, [r11, r5]
		add		r4, r4, #4
		add		r5, r5, #-4
		ldrb		r6, [r1, r4]
		cmp		r6, #0
		bne		whileS2
		mov		PC, LR
		
hello	DCD		104, 101, 108, 108, 111, 0
		;hello	DCD		0x006F6C6C6568
goodbye	DCD		103, 111, 111, 100, 98, 121, 101, 0
		;goodbye	DCD		0x00657962646F6F67
