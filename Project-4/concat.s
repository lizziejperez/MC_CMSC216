main
		;		setup FP(r11) and SP(r13)
		str		r11, [r13, #-4]!
		mov		r11, r13
		;		storing LR at FP-8
		sub		r13, r13, #-8
		str		LR, [r11, #-8]
		;		setup vars: s1(r3), len1(r2), s2(r1), len2(r0)
		mov		r3, #hello
		mov		r2, #5
		mov		r1, #goodbye
		mov		r0, #7
		;		storing len2 at FP-12
		sub		r13, r13, #-4
		str		r0, [r11, #-12]
		;		storing (len1 + len2 + 1) in r0
		add		r0, r0, r2
		add		r0, r0, #1
		;		branch links to _allocate
		bl		_allocate
		;		stores value in r0 (the return value of _allocate) in result(r4)
		mov		r4, r0
		;		restoring len2(r0) from FP-12
		ldr		r0, [r11, #-12]
		add		r13, r13, #4
		;		setup ix4(r5)
		mov		r5, #0
		;		branch links to whileS1 if the value in r6 (the first char/byte in s1) != 0
		ldrb		r6, [r3, r5]
		cmp		r6, #0
		blne		whileS1
		;		branch links to whileS1 if the value in r6 (the first char/byte in s2) != 0
		mov		r7, #0
		ldrb		r6, [r1, r7]
		cmp		r6, #0
		blne		whileS2
		;		stores result in r0
		mov		r0, r4
		;		restoring LR from FP-8
		ldr		LR, [r11, #-8]
		add		r13, r13, #8
		end
		
_allocate
		;		setup free_mem_ptr(r6) and MAX_MEM_ADDR(r7)
		mov		r6, #0x800
		mov		r7, #0x1800
		;		branchs to ifSpace if the value in r8 (free_mem_ptr+r0) <= MAX_MEM_ADDR
		add		r8, r6, r0
		cmp		r8, r7
		ble		ifSpace
		;		sets r0 to 0 and exits branch link
		mov		r0, #0
		mov		PC, LR
ifSpace
		;		sets r0 to free_mem_ptr and exits branch link
		mov		r0, r6
		mov		PC, LR

whileS1
		;		stores the value in r6 (a char in s1) at result(r4)+r5
		str		r6, [r4, r5]
		;		increments r5 by 4 (the next char length)
		add		r5, r5, #4
		;		branchs to whileS1 if the value in r6 (the next char in s1) != 0
		ldrb		r6, [r3, r5]
		cmp		r6, #0
		bne		whileS1
		;		exits branch link
		mov		PC, LR

whileS2
		;		stores the value in r6 (a char in s2) at result(r4)+r5
		str		r6, [r4, r5]
		;		increments r5 and r7 by 4 (the next char length)
		add		r5, r5, #4
		add		r7, r7, #4
		;		branchs to whileS2 if the value in r6 (the next char in s2) != 0
		ldrb		r6, [r1, r7]
		cmp		r6, #0
		bne		whileS2
		;		exits branch link
		mov		PC, LR

hello	DCD		104, 101, 108, 108, 111, 0
goodbye	DCD		103, 111, 111, 100, 98, 121, 101, 0
