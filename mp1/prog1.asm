;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; This piece of the program print the histogram of the number of each character 
; and non-alphabetic characters. The count of non-alphabetic characters and each 
; character are stored from x3F00(A) to x3F1A(Z).

; table of register use in this part of the code
;    R0 holds the value to be printed on the monitor
;    R1 holds the bit counter
;    R2 holds the digit counter
;    R3 holds the count of each character
;    R4 holds the ASCII value of character A-Z
;    R5 holds the memory location of count of each character
;    R6 is used as a temporary register("A" or "0"+10)
;    R7 holds the counter for bins of histogram

		LD R6,NUM_BINS  ; Initialize the loop counter to 27
		LD R4,AT	; Initialize the R4 to "@"
		LD R5,COUNTS	; Initialize the R5 to the memory location of the count of non-alphabetic characters
OUTLOOP		AND R0,R0,#0	; Initialize the R0 to 0
		ADD R0,R0,R4	; Store the ASCII value of character to R0
		OUT		; Print the character
		LD R0,SPACE	; Store the ASCII value of Space to R0
		OUT		; Print Space
		LDR R3,R5,#0	; Load the count of the character to R3
		AND R2,R2,#0	; Initialize R2
		ADD R2,R2,#4	; Initialize the digit counter to 4
LOOP1		AND R0,R0,#0	; Clear R0
		AND R1,R1,#0	; Initialize R1
		ADD R1,R1,#4	; Initialize the bit counter to 4
LOOP2		ADD R0,R0,R0	; Left shift R0
		ADD R3,R3,#0	; Set CC
		BRzp ZERO	; If the MSB of R3 is 0, branch to ZERO
		ADD R0,R0,#1	; ADD 1 to R0 if the MSB of R3 is 1
ZERO		ADD R3,R3,R3	; Left shift R3
		ADD R1,R1,#-1	; Decrement the counter
		BRp LOOP2	; Branch to Loop2 if the counter is 0
		ADD R0,R0,#-10	; R0 = R0 - 10
		BRn LESS	; Chech whether R0 is less then 10
		LD R7,A		; Load "A" to R7
		ADD R0,R0,R7	; Change to ASCII value
		BRnzp NEXT	; Always Branch to NEXT
LESS		LD R7,ZEROTEN 	; Load "0"-10 to R7
		ADD R0,R0,R7	; Change to ASCII value
NEXT		OUT		; Print the corresponding ASCII value
		ADD R2,R2,#-1	; Decrement the counter
		BRp LOOP1	; Brach to LOOP of the counter is positive
		LD R0,NEWLINE	; Load Newline to R0
		OUT		; Print Newline
		ADD R4,R4,#1	; Change to next character
		ADD R5,R5,#1	; Change to the location of the count of the next character
		ADD R6,R6,#-1	; Decrement the counter
		BRp OUTLOOP	; Branch to OUTLOOP if the counter is positive
DONE		HALT			; done		
		
		


A		.Fill x0041	; ASCII value of "A"
ZEROTEN		.FILL x003A	; ASCII value of "0" - 10
AT		.FILL x0040	; ASCII value of @
COUNTS		.FILL x3F00	; Location of the count of the non-alphabetic characters
NEWLINE 	.FILL x000A	; ASCII value of newline
SPACE		.FILL x0020	; ASCII value of space




; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
