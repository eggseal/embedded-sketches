// DIVISION
// Takes one number M[1] and calculates the integer division between another number M[2], stores it on M[0]

// Declare result as 0
@0
M=0

(LOOP)
// Get M[1] and subtract M[2] from it
@1
D=M
@2
D=D-M

// Go to the end if the numerator is smaller than the denominator
@END
D;JLT

// Subtract the denominator from the numerator
@1
D=M
@2
D=D-M
@1
M=D

// Increment the counter result
@0
M=M+1

// Go back to loop beginning
@LOOP
0;JMP

(END)
@END
0;JMP