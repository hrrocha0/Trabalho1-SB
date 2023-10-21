; Lê um número e retorna 1, se for par, ou 0, se for ímpar.
; 12 20 10 20 4 23 3 23 2 20 8 14 5 17 13 22 14 13 21 14 0 0 1 2
SECAO	DATA
X:		SPACE			; 20
ZERO:	CONST	0		; 21
ONE:	CONST	1		; 22
TWO:	CONST	2		; 23

SECAO	TEXT
MAIN:	INPUT	X		; 0
		LOAD	X		; 2
		DIV		TWO		; 4
		MUL		TWO		; 6
		SUB		X		; 8
		JMPZ	PAR		; 10
		JMP		IMPAR	; 12

PAR:	OUTPUT	ONE		; 14
		STOP			; 16

IMPAR:	OUTPUT	ZERO	; 17
		STOP			; 19
