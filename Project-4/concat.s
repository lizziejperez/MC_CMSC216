main
		mov		r3, #hello
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
		end

ALLOC
		

hello	DCD		104, 101, 108, 108, 111, 0
goodbye	DCD		103, 111, 111, 100, 98, 121, 101, 0