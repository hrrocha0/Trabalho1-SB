; Calcula a raiz quadrada de um número.
; 12 29 9 32 30 9 32 31 10 31 3 31 2 29 7 26 10 31 11 30 1 33 11 31 5 8 13 30 14 0 0 0 0 1
secao	text
		input	x			; 0
		copy	zero,r		; 2
		copy	zero,aux	; 5
loop:	load	aux			; 8
		mul		aux			; 10
		sub		x			; 12
		jmpp	break		; 14
		load	aux			; 16
		store	r			; 18
		add		one			; 20
		store	aux			; 22
		jmp		loop		; 24
break:	output	r			; 26
		stop				; 28
secao	data
x:		space				; 29
r:		space				; 30
aux:	space				; 31
zero:	const	0			; 32
one:	const	1			; 33
