; mp2
; Zining Ge - ziningg2
;
; This program is about to evaluate and calculate 
;   a postfix expression by using the stack storage.
; The valid characters are only numbers between 0 - 9 
;   and operation symbols '+', '-', '*', '/', '^'
; A space is also allowed
; By typing '=' to end the expression and reutrn the result
; partners: mingzx2, ziningg2
;
;
.ORIG x3000
	
;your code goes here

	JSR EVALUATE	; run the evaluate subroutine



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX
	AND R3,R3,#0
	ADD R3,R3,R5	; stores R5 into R3
	AND R2,R2,#0
	ADD R2,R2,#4	; Initialize the digit counter to 4 
LOOP1 
	AND R0,R0,#0	; Clear R0 
	AND R1,R1,#0	; Initialize R1 
	ADD R1,R1,#4	; Initialize the bit counter to 4 
LOOP2
	ADD R0,R0,R0	; Left shift R0 
	ADD R3,R3,#0	; Set CC 
	BRzp ZERO		; If the MSB of R3 is 0, branch to ZERO 
	ADD R0,R0,#1	; ADD 1 to R0 if the MSB of R3 is 1 
ZERO
	ADD R3,R3,R3	; Left shift R3 
	ADD R1,R1,#-1	; Decrement the counter 
	BRp LOOP2		; Branch to Loop2 if the counter is 0 
	ADD R0,R0,#-10	; R0 = R0 - 10 
	BRn LESS		; Chech whether R0 is less then 10 
	LD R6,A		; Load "A" to R7 
	ADD R0,R0,R6	; Change to ASCII value 
	BRnzp NEXT	; Always Branch to NEXT 
LESS
	LD R6,ZEROTEN	; Load "0"-10 to R7 
	ADD R0,R0,R6	; Change to ASCII value 
NEXT
	OUT			; Print the corresponding ASCII value 
	ADD R2,R2,#-1	; Decrement the counter 
	BRp LOOP1		; Brach to LOOP of the counter is positive 
	HALT
  
  A .FILL x0041 
  ZEROTEN .FILL x003A
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE

;your code goes here

MAINLOOP
	GETC
	OUT
	LD R2, NEGEQUAL
	ADD R2, R2, R0	; check if the char is ‘=‘
	BRz EQUAL
	LD R2, NEGSPACE
	ADD R2, R2, R0	; check if the char is ‘ ‘
	BRz MAINLOOP

	LD R2, NEGPLUS
	ADD R2, R2, R0 ; check if the char is ‘+’
	BRz PLUS_SUB

	LD R2, NEGMINUS
	ADD R2, R2, R0 ; check if the char is ‘-’
	BRz MINUS_SUB

	LD R2, NEGMUL
	ADD R2, R2, R0 ; check if the char is ‘*’
	BRz MUL_SUB

	LD R2, NEGDIV
	ADD R2, R2, R0 ; check if the char is ‘/’
	BRz DIV_SUB

	LD R2, NEGEXP
	ADD R2, R2, R0 ; check if the char is ‘^’
	BRz EXP_SUB

	LD R2, NEGZERO
	ADD R2, R2, R0 ; check if the char is less than ‘0’
	BRn INVALID_CHAR

	LD R2, NEGNINE
	ADD R2, R2, R0 ; check if the char is greater than ‘9’
	BRp INVALID_CHAR

STORE_NUM
	LD R2, NEGZERO
	ADD R0, R0, R2 ; convert R0 into a numerical value
	JSR PUSH
	BRnzp MAINLOOP	; loop back

PLUS_SUB
	JSR POP
	ADD R5, R5, #0
	BRp INVALID_CHAR
	AND R4, R4, #0
	ADD R4, R4, R0	; store the first pop value in R4
	JSR POP
	ADD R5, R5, #0
	BRp INVALID_CHAR
	AND R3, R3, #0
	ADD R3, R3, R0	; store the second pop value in R4

	JSR PLUS		; run the plus subroutine
	JSR PUSH		; push the result
	BRnzp MAINLOOP	; loop back
	
MINUS_SUB
	JSR POP
	ADD R5, R5, #0
	BRp INVALID_CHAR
	AND R4, R4, #0
	ADD R4, R4, R0	; store the first pop value in R4
	JSR POP
	ADD R5, R5, #0
	BRp INVALID_CHAR
	AND R3, R3, #0
	ADD R3, R3, R0	; store the second pop value in R4

	JSR MIN		; run the minus subroutine
	JSR PUSH		; push the result
	BRnzp MAINLOOP	; loop back

MUL_SUB
	JSR POP
	ADD R5, R5, #0
	BRp INVALID_CHAR
	AND R4, R4, #0
	ADD R4, R4, R0	; store the first pop value in R4
	JSR POP
	ADD R5, R5, #0
	BRp INVALID_CHAR
	AND R3, R3, #0
	ADD R3, R3, R0	; store the second pop value in R4

	JSR MUL		; run the multiplication subroutine
	JSR PUSH		; push the result
	BRnzp MAINLOOP	; loop back

DIV_SUB
	JSR POP
	ADD R5, R5, #0
	BRp INVALID_CHAR
	AND R4, R4, #0
	ADD R4, R4, R0	; store the first pop value in R4
	JSR POP
	ADD R5, R5, #0
	BRp INVALID_CHAR
	AND R3, R3, #0
	ADD R3, R3, R0	; store the second pop value in R4

	JSR DIV		; run the division subroutine
	JSR PUSH		; push the result
	BRnzp MAINLOOP	; loop back

EXP_SUB
	JSR POP
	ADD R5, R5, #0
	BRp INVALID_CHAR
	AND R4, R4, #0
	ADD R4, R4, R0	; store the first pop value in R4
	JSR POP
	ADD R5, R5, #0
	BRp INVALID_CHAR
	AND R3, R3, #0
	ADD R3, R3, R0	; store the second pop value in R4

	JSR EXP		; run the exponentiation subroutine
	JSR PUSH		; push the result
	BRnzp MAINLOOP	; loop back

EQUAL
	LD R2, NEGSTART_MO
	LD R6, STACK_TOP
	ADD R2 ,R2, R6	; check if there is only one element in the stack
	BRz ONLYONE
INVALID_CHAR
	LEA R0, INVALID
	PUTS
	BRnzp DONE	; the expression is invalid

ONLYONE
	JSR POP
	ADD R5, R5, R0	; stores the result into R5
	JSR PRINT_HEX
	
	RET
DONE
	HALT

	NEGSPACE	.FILL xFFE0	;
	NEGPLUS .FILL xFFD5   ;
	NEGMINUS .FILL xFFD3
	NEGMUL .FILL xFFD6
	NEGDIV .FILL xFFD1
	NEGEXP .FILL xFFA2
	NEGZERO .FILL xFFD0
	NEGNINE .FILL xFFC7
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
;your code goes here

	ADD R0, R3, R4		; Add R3 and R4
	RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here

	NOT R4, R4		; 
	ADD R4, R4, #1		; negate R4
	ADD R0, R3, R4		; R3 - R4
	RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here

	AND R0, R0, #0		; initialize R0 to 0
	MUL_LOOP
	ADD R4, R4, #-1	; decrement R4
	BRn MUL_DONE		; R4 is zero, so as the result
	ADD R0, R0, R3		; Add R3 to R0
	BRp MUL_LOOP		; loop again if R4 is still positive

MUL_DONE
	RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here

	AND R0, R0, #0		; initialize R0 to 0
	NOT R4, R4		; 
	ADD R4, R4, #1		; negate R4
	BRz DIVID_ZERO		; R4 is zero, division cannot be performed
	DIVID_LOOP
	ADD R3, R3, R4		; R3 subtracts one R4
	BRn DIVID_DONE		; Division is finished
	ADD R0, R0, #1		; increment R0
	BRnzp DIVID_LOOP	; Loop again

DIVID_DONE
	RET

DIVID_ZERO		; a zero appears, there is an error
	LEA R0, INVALID
	PUTS
	HALT
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here
	ST R7, R7_VAL
	AND R0, R0, #0		; initialize R0 to 0
	ADD R4, R4, #0		; test if R4 is zero
	BRz EXP_ZERO
	AND R1, R1, #0		;
	ADD R1, R1, R4		; stores the value of R4 into R1
	ST R3, ORIGIN_NUM
	
EXP_LOOP
	LD R4, ORIGIN_NUM
	ADD R1, R1, #-1	; decrement R1 for counting the loop
	BRz EXP_DONE		; exp is finished
	JSR MUL
	AND R3, R3, #0
	ADD R3, R3, R0		; store the value of R0 into R3
	BRnzp EXP_LOOP		; loop back
	
EXP_DONE
	AND R0, R0, #0		; reset R0
	ADD R0, R0, R3		; R0 stores the value in R3
	LD R7, R7_VAL
	RET

EXP_ZERO
	ADD R0, R0, #1		; the result is 1
	LD R7, R7_VAL
	RET
  
 	ORIGIN_NUM .FILL x0000
 	R7_VAL .FILL x0000
	
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACK_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET

POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;
NEGSTART_MO	.FILL xC001	;
NEGEQUAL	.FILL xFFC3	;
INVALID		.STRINGZ "Invalid_Expression"	;

.END

