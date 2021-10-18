main:
	mov r3, #1085129359	;5.43=0x40adc28f
	mov r4, #0
	str r4, [fp, #-4]	;dollars
	str r4, [fp, #-8]	;quarters
	str r4, [fp, #-12]	;dimes
	str r4, [fp, #-16]	;nickels
	str r4, [fp, #-20]	;pennies
