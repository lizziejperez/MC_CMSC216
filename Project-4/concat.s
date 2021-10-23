main
		;		setup
		str		r11, [r13, #-4]!
		sub		r13, r13, #-24

		mov		r3, #hello
		mov		r2, #5
		mov		r1, #goodbye
		mov		r0, #7

		str		r0, [r13, #-4]
		add		r0, r0, r2
		add		r0, r0, #1
		bl		_allocate
		ldr		r0, [r13, #-4]

		; 1 - while *s1 != #0
		cmp		r3, #0
		blt		whileS1
		; 1 - while *s1 != #0
		cmp		r1, #0
		blt		whileS2
		;		clean up
		add		r13, r13, #24
		ldr		r11, [r13, #4]
		end

_allocate
		sub		r13, r13, r0

whileS1
		; goes thru each character in s1 (r3) and adds it into result at index i (r?)
		; the index i and s1 are incrementing each iteration
		; note: ldrb	r5, [r3,#4] second letter
whileS2

hello	DCD		104, 101, 108, 108, 111, 0
;hello DCD		0x 00 6F 6C 6C 65 68
goodbye	DCD		103, 111, 111, 100, 98, 121, 101, 0
;goodbye DCD		0x 00 65 79 62 64 6F 6F 67