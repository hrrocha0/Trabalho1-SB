; Calcula o fatorial de um número.
; 12 27 9 27 28 9 27 29 10 29 2 30 11 29 10 28 3 29 11 28 5 8 13 28 14 0 0 0 1
SECAO	TEXT

INPUT	X			; 0
COPY	X,R			; 2
COPY	X,AUX		; 5

LOOP:
LOAD	AUX			; 8
SUB		ONE			; 10
STORE	AUX			; 12
JMPZ	BREAK		; 14
LOAD	R			; 16
MUL		AUX			; 18
STORE	R			; 20
JMP		LOOP		; 22

BREAK:
OUTPUT	R			; 24
STOP				; 26

SECAO	DATA

X:		SPACE		; 27
R:		SPACE		; 28
AUX:	SPACE		; 29
ONE:	CONST	1	; 30