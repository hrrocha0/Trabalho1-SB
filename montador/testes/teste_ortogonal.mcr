; Verifica se dois vetores tridimensionais são ortogonais.
; 12 45 12 46 12 47 12 48 12 49 12 50 10 45 3 48 11 51 10 46 3 49 1 51 11 51 10 47 3 50 1 51 11 51 10 51 8 42 13 52 5 44 13 53 14 0 0 0 0 0 0 0 0 1
INPUT3:	MACRO	&A
		INPUT	&A			; +0
		INPUT	&A+1		; +2
		INPUT	&A+2		; +4
ENDMACRO

DOT:	MACRO	&A, &B, &C
		LOAD	&A			; +0
		MUL		&B			; +2
		STORE	&C			; +4
		LOAD	&A+1		; +6
		MUL		&B+1		; +8
		ADD		&C			; +10
		STORE	&C			; +12
		LOAD	&A+2		; +14
		MUL		&B+2		; +16
		ADD		&C			; +18
		STORE	&C			; +20
ENDMACRO

SECAO	DATA
X:		SPACE	3			; 45
Y:		SPACE	3			; 48
Z:		SPACE				; 51

SECAO	TEXT
		INPUT3	X			; 0
		INPUT3	Y			; 6
		DOT		X	Y	Z	; 12
		LOAD	Z			; 34
		JMPZ	TRUE		; 36
		OUTPUT	ZERO		; 38
		JMP		EXIT		; 40
TRUE:	OUTPUT	ONE			; 42
EXIT:	STOP				; 44

SECAO	DATA
ZERO:	CONST	0			; 52
ONE:	CONST	1			; 53
