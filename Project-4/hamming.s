main
			;		input(r3), output (r0), position(r2)
			mov		r3, #138
			mov		r2, #0
			mov		r0, #0
			;		WORD_SIZE(r1), bit(r4)
			mov		r1, #16
			mov		r4, #1
			
			cmp		r4, r1
			bllt		forBit0 ; bit < WORD_SIZE
			
			cmp		r2, #0
			blne		ifPosition ; position != 0
			
			END
			
forBit0
			;		parity(r5), pos(r6)
			mov		r5, #0
			mov		r6, #1
			cmp		r6, r1
			ble		forPos0 ; pos <= WORD_SIZE
forBit1
			and		r7, r5, #1
			cmp		r7, #0
			bne		ifParity ; (pos & 1) != 0
forBit2
			lsl		r4, r4, #1
			cmp		r4, r1
			blt		forBit0 ; bit < WORD_SIZE
			mov		PC, LR
			
forPos0
			and		r7, r6, r4
			cmp		r7, #0
			beq		forPos1 ; (pos & bit) == 0
			sub		r7, r1, r6
			lsr		r8, r3, r7
			and		r7, r8, #1
			cmp		r7, #0
			beq		forPos1 ; ((input >> (WORD_SIZE-pos)) & 1) == 0
			add		r5, r5, #1
forPos1
			add		r6, r6, #1
			cmp		r6, r1
			ble		forPos0 ; pos <= WORD_SIZE
			b		forBit1
			
			
ifParity
			add		r2, r2, r4
			b		forBit2
			
ifPosition
			sub		r2, r1, r2
			mov		r7, #1
			lsl		r8, r7, r2
			eor		r0, r3, r8
			mov		PC, LR
