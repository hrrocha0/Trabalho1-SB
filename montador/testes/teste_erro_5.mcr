; Erro semântico: rótulos repetidos
M1:		MACRO	&A
LOOP:	OUTPUT	&A
		LOAD	&A
		SUB		ONE
		STORE	&A
		JMPP	LOOP
ENDMACRO
SECAO	TEXT
		INPUT	X
		INPUT	Y
		M1		X
		M1		Y
		STOP
SECAO	DATA
X:		SPACE
Y:		SPACE
ONE:	CONST	1