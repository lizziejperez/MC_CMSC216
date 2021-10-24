main
		;		setup vars: input(r3), output (r0), position(r2), WORD_SIZE(r1)
		mov		r3, #138
		mov		r2, #0
		mov		r0, #0
		mov		r1, #16
		;		setup bit(r4) and branch links to forBit0 if bit < WORD_SIZE
		mov		r4, #1
		cmp		r4, r1
		bllt		forBit0
		;		branch links to ifPosition if position != 0
		cmp		r2, #0
		blne		ifPosition
		end

forBit0
		;		setup parity(r5) and pos(r6)
		mov		r5, #0
		mov		r6, #1
		;		branches to forPos0 if pos <= WORD_SIZE
		cmp		r6, r1
		ble		forPos0
forBit1
		;		branches to ifParity if (pos & 1) != 0
		and		r7, r5, #1
		cmp		r7, #0
		bne		ifParity
forBit2
		;		branches to forBit0 if bit < WORD_SIZE
		lsl		r4, r4, #1
		cmp		r4, r1
		blt		forBit0
		;		exits branch link
		mov		PC, LR
			
forPos0
		;		branches to forPos1 if (pos & bit) == 0
		and		r7, r6, r4
		cmp		r7, #0
		beq		forPos1
		;		branches to forPos1 if ((input >> (WORD_SIZE-pos)) & 1) == 0
		sub		r7, r1, r6
		lsr		r8, r3, r7
		and		r7, r8, #1
		cmp		r7, #0
		beq		forPos1
		;		increments parity by 1
		add		r5, r5, #1
forPos1
		;		increments pos by 1
		add		r6, r6, #1
		;		brances to forPos0 if pos <= WORD_SIZE
		cmp		r6, r1
		ble		forPos0
		;		branches to forBit1
		b		forBit1

ifParity
		;		increments position by bit
		add		r2, r2, r4
		;		branches to forBit2
		b		forBit2

ifPosition
		;		sets position to WORD_SIZE - position
		sub		r2, r1, r2
		;		sets output to input ^ (1 << position)
		mov		r7, #1
		lsl		r8, r7, r2
		eor		r0, r3, r8
		;		exits branch link
		mov		PC, LR