; Name: Elizabeth Perez
; Student ID: eperez57
; M-number: M20966722

main
		;		setup FP(r11) and SP(r13)
		str		r11, [r13, #-4]!
		mov		r11, r13
		sub		r13, r13, #-20
		
		;		setup vars: amount(r3.r4), dollars(FP-4), quarters(FP-8), dimes(FP-12), nickels(FP-16), pennies(FP-20)
		mov		r3, #5
		mov		r4, #43
		mov		r5, #0
		str		r5, [r11, #-4]
		str		r5, [r11, #-8]
		str		r5, [r11, #-12]
		str		r5, [r11, #-16]
		str		r5, [r11, #-20]
		
		;		stores the integer portion of amount (value in r3) in dollars
		str		r3, [r11, #-4]
		;		sets a remainder(r5) to the decimal portion of amount
		mov		r5, r4
		;		sets a divisor(r6) to 25 and branch links to divide0
		mov		r6, #25
		bl		divide0
		str		r7, [r11, #-8]
		;		sets a divisor(r6) to 10 and branch links to divide0
		mov		r6, #10
		bl		divide0
		str		r7, [r11, #-12]
		;		sets a divisor(r6) to 5 and branch links to divide0
		mov		r6, #5
		bl		divide0
		str		r7, [r11, #-16]
		;		stores the value in r5 (the remainder) in pennies
		str		r5, [r11, #-20]
		
		;		restore FP and SP
		add		r13, r13, #20
		ldr		r11, [r13, #4]!
		END
		
divide0
		;		sets a counter(r7) to 0
		mov		r7, #0
divide1
		;		branches to divide2 if the remainder(r5) >= the divisor(r6)
		cmp		r5, r6
		bge		divide2
		;		exits branch link
		mov		PC, LR
divide2
		;		increments the counter(r7) by 1 and decrements the remainder(r5) by the divisor(r6)
		add		r7, r7, #1
		sub		r5, r5, r6
		;		branches to divide1
		b		divide1
