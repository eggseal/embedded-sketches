// MULTIPLICATION
// Takes one number M[1] and multiplies it by another number M[2], retreives the result M[0]

// Declare result as 0
@0
M=A

// Declare iterator as 0
@i
M=0

(LOOP)
// Get iterator
@i
D=M
// Subtract multiplier (at 2)
@2
D=D-M
// If iterator >= multiplier jump to the end
@END
D;JGE

// Or else, get result
@0
D=M
// Add value (at 1) to the result
@1
D=D+M
// Store the sum
@0
M=D

// Increment iterator;
@i
M=M+1
// Go to loop beginning
@LOOP
0;JMP
 
(END)
@END
0;JMP




