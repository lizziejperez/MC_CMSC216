main
		;		setup
		str		r11, [r13, #-4]!
		sub		r13, r13, #-20
		;		input(r3), output (r0), position(r2)
		mov		r3, #138
		mov		r2, #0
		mov		r0, #0
		;		bit(r?), parity(r?), pos(r?)
		
		;		clean up
		add		r13, r13, #20
		ldr		r11, [r13, #4]
		END