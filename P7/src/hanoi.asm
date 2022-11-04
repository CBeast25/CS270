; Description: LC3 Tower of Hanoi Implementation 

; Your name goes here

;------------------------------------------------------------------------------
; BEGIN_RESERVED_SECTION: do not change ANYTHING in reserved the section!
; The ONLY exception to this is that you MAY change the .FILL value for
; any memory location marked for modification. This makes debugging easier
; as you need only change your code and re-assemble. Your test value(s) will
; already be set.

                .ORIG x3000
                BR main

option          .FILL 0  ; YOU_MAY_MODIFY_VAL ; 0 => Hanoi, non-0 => printMove
numDisks        .FILL 4  ; YOU_MAY_MODIFY_VAL
startTower      .FILL 1  ; YOU_MAY_MODIFY_VAL
endTower        .FILL 3  ; YOU_MAY_MODIFY_VAL

                ; misc strings for printing
digits          .STRINGZ "0123456789"
msg1            .STRINGZ "Move disk ";
msg2            .STRINGz " from tower ";
msg3            .STRINGz " to tower ";
endMsg          .STRINGz "\nThe world has ended\n"

stack           .FILL 0x4000

main            LD   R6,stack           ; initialize stack
                LD   R5,stack           ; initialize frame pointer

                LD   R0,endTower        ; both function have three parameters
                PUSH R0                 ; so put them on stack before JSR
                LD   R0,startTower
                PUSH R0
                LD   R0,numDisks
                PUSH R0

                LD   R0,option          ; get option to test
                BRZ  testHanoi

testPrintMove   JSR  printMove
                BR   endTest

testHanoi       JSR  hanoi

endTest         ADD  R6,R6,#3           ; clean up parameters
                LEA  R0,endMsg
                PUTS
theEnd          HALT                    ; check R5, R6 here, should be initial 'stack' value

; END_RESERVED_SECTION

;----  S t u d e n t   c o d e   g o e s   h e r e  --------------------------

; void printMove(disk, from, to)

; disk @ FP   ; from at FP   ; to @ FP   ; complete line
endLine .FILL '\n'

printMove	
				PUSH R7
				PUSH R5
				ADD R5,R6,#-1
				LEA R1,digits
				LEA R0,msg1
				PUTS
				LDR R0,R5,#3
				ADD R0,R0,R1
				LDR R0,R0,#0
				OUT
				LEA R0,msg2
				PUTS
				LDR R0,R5,#4
				ADD R0,R0,R1
				LDR R0,R0,#0
				OUT
				LEA R0,msg3
				PUTS
				LDR R0,R5,#5
				ADD R0,R0,R1
				LDR R0,R0,#0
				OUT
				LD R0,endLine
				OUT
				POP R5
				POP R7
                RET                     ; return to caller

;------------------------------------------------------------------------------
 
; void hanoi(numDisks, fromDisk, toDisk)

; numDisks @ R5   ; fromTower @ R5   ; toTower @ R5   ; auxTower @ R5   ; complete line
six	.FILL 6

hanoi
				PUSH R7
				PUSH R5
				ADD R5,R6,#-1
				ADD R6,R6,#-1				
				LDR R0,R5,#3
				ADD R0,R0,#-1
				BRnp else
				
				LDR R0,R5,#5
				PUSH R0
				LDR R0,R5,#4
				PUSH R0
				LDR R0,R5,#3
				PUSH R0
				JSR printMove
				ADD R6,R6,#3
				BRnzp fin
				
else		
				LD R0,six
				LDR R1,R5,#4
				LDR R2,R5,#5
				ADD R1,R1,R2
				NOT R1,R1
				ADD R1,R1,#1
				ADD R0,R0,R1
				STR R0,R5,#0
				
				PUSH R0
				LDR R0,R5,#4
				PUSH R0
				LDR R0,R5,#3
				ADD R0,R0,#-1
				PUSH R0
				JSR hanoi
				ADD R6,R6,#3
				
				LDR R0,R5,#5
				PUSH R0
				LDR R0,R5,#4
				PUSH R0
				LDR R0,R5,#3
				PUSH R0
				JSR printMove
				ADD R6,R6,#3
				
				LDR R0,R5,#5
				PUSH R0
				LDR R0,R5,#0
				PUSH R0
				LDR R0,R5,#3
				ADD R0,R0,#-1
				PUSH R0
				JSR hanoi
				ADD R6,R6,#3
fin				
				ADD R6,R6,#1
				POP R5
				POP R7
                RET                     ; return to caller
;------------------------------------------------------------------------------
                .END
