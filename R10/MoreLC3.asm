; Recitation MoreLC3
; Author: <name>
; Date:   <date>
; Email:  <email>
; Class:  CS270
; Description: Mirrors least significant byte to most significant
;--------------------------------------------------------------------------
; Begin reserved section: do not change ANYTHING in reserved section!

            .ORIG x3000

            JSR mirror               ; call function
            HALT

; Parameter and return value
Param           .BLKW 1              ; space to specify parameter
Result          .BLKW 1              ; space to store result

; Constants
One             .FILL #1             ; the number 1       
Eight           .FILL #8             ; the number 8
Mask            .FILL x00ff          ; mask top bits

; End reserved section: do not change ANYTHING in reserved section!
;--------------------------------------------------------------------------
mirror                           ; Mirrors bits 7:0 to 15:8
                                 ; ~20 lines of assembly code

            LD R0,Param          ; load pattern
                                 ; your code here
	    LD R2,One
	    LD R3,One
	    LD R1,Mask
	    AND R1,R0,R1
	    LD R4,Eight
Loop1
	    ADD R3,R3,R3
	    ADD R4,R4,#-1
	    BRp Loop1
	    LD R4,Eight
Loop2	    
	    AND R5,R0,R2	 ; Check if current bit is a one
	    BRz Miss
	    NOT R5,R3		 ; OR with Eight and R1 to copy bit
	    NOT R6,R1
	    AND R5,R6,R5
	    NOT R1,R5
Miss	    
	    ADD R2,R2,R2	 ; Left shift One and Eight
	    ADD R3,R3,R3
	    ADD R4,R4,#-1
	    BRp Loop2
	    	    
            ST R1,Result         ; store result
            RET
;--------------------------------------------------------------------------
           .END
