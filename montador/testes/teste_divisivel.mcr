; Verifica se um número é divisível pelo outro.
; 12 28 12 29 10 28 4 29 3 29 11 29 10 28 2 29 11 29 10 29 8 25 13 30 14 13 31 14 0 0 0 1
MOD:	MACRO	&A, &B, &C
		LOAD	&A					; +0
		DIV		&B					; +2
		MUL		&B					; +4
		STORE	&C					; +6
		LOAD	&A					; +8
		SUB		&C					; +10
		STORE	&C					; +12
ENDMACRO

JMPDIV:	MACRO	&A, &B, &C
		MOD		&A	&B	&B			; +0
		LOAD	&B					; +14
		JMPZ	&C					; +16
ENDMACRO

SECAO	TEXT
MAIN:	INPUT	M					; 0
		INPUT	N					; 2
		JMPDIV	M	N	DIVISIVEL	; 4
		OUTPUT	ZERO				; 22
		STOP						; 24

DIVISIVEL:
		OUTPUT	UM					; 25
		STOP						; 27

SECAO	DATA
M:		SPACE						; 28
N:		SPACE						; 29
ZERO:	CONST	0					; 30
UM:		CONST	1					; 31
