; Verifica se um número é divisível pelo outro.
; 12 25 12 26 10 25 4 26 3 26 11 26 10 25 2 26 8 22 13 27 5 24 13 28 14 0 0 0 1
JMPDIV:	MACRO	&A, &B, &C
		LOAD	&A				; +0
		DIV		&B				; +2
		MUL		&B				; +4
		STORE	&B				; +6
		LOAD	&A				; +8
		SUB		&B				; +10
		JMPZ	&C				; +12
ENDMACRO

SECAO	DATA
X:		SPACE					; 25
Y:		SPACE					; 26
ZERO:	CONST	0				; 27
ONE:	CONST	1				; 28

SECAO	TEXT
		INPUT	X				; 0
		INPUT	Y				; 2
		JMPDIV	X	Y	TRUE	; 4
		OUTPUT	ZERO			; 18
		JMP		EXIT			; 20
TRUE:	OUTPUT	ONE				; 22
EXIT:	STOP					; 24
