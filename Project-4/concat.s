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

		;		While loops (ldrb	r5, [r3,#4] second letter)

		;		clean up
		add		r13, r13, #24
		ldr		r11, [r13, #4]
		end

_allocate
		

hello	DCD		104, 101, 108, 108, 111, 0
goodbye	DCD		103, 111, 111, 100, 98, 121, 101, 0