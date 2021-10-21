main
		;		setup
		str		r11, [r13, #-4]!
		sub		r13, r13, #-20
		
		;		input(r3), output (r0), position(r2)
		mov		r3, #138
		mov		r2, #0
		mov		r0, #0
		;		WORD_SIZE(r1), bit(r4) 
		mov		r1, #16
		mov		r4, #1
		cmp		r4, r1
		blt		forBit
		
		;		clean up
		add		r13, r13, #20
		ldr		r11, [r13, #4]
		END

forBit
		;		parity(r5), pos(r6)
		mov		r5, #0
		mov		r6, #1
		cmp		r6, r1
		ble		forPos
		;(parity & 1)

forPos
ifParity
ifPosition