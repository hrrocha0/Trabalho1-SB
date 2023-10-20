; Calcula a potência de um número.
; 12 26 12 27 9 26 28 10 27 2 29 11 27 8 23 10 28 3 26 11 28 5 7 13 28 14 0 0 0 1

SECAO	DATA
X:		SPACE			; 26
Y:		SPACE			; 27
R:		SPACE			; 28
ONE:	CONST	1		; 29

SECAO	TEXT
		INPUT	X		; 0
		INPUY	Y		; 2
		COPY	X,R		; 4
LOOP:	LOAD	Y		; 7
		SUB		ONE		; 9
		STORE	Y		; 11
		JMPZ	BREAK	; 13
		LOAD	R		; 15
		MUL		X		; 17
		STORE	R		; 19
		JMP		LOOP	; 21
BREAK:	OUTPUT	R		; 23
		STOP			; 25
