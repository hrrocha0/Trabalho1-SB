; Calcula a média aritmética de dois números.
; 12 15 12 16 10 15 1 16 4 18 11 17 13 17 14 0 0 0 2

SECAO	TEXT
MAIN:	INPUT	X	; 0
		INPUT	X+1	; 2
		LOAD	X	; 4
		ADD		X+1	; 6
		DIV		TWO	; 8
		STORE	R	; 10
		OUTPUT	R	; 12
		STOP		; 14

SECAO	DATA
X:		SPACE	2	; 15
R:		SPACE		; 17
TWO:	CONST	2	; 1810
