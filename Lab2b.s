/*Author - Lab Tech. Last edited on Jan 14, 2022 */
/*
Name: David Ola 
CCID: 1811947
Name: Kavin Kumaran 
CCID: 1805173
*/
/*-----------------DO NOT MODIFY--------*/
.global TestAsmCall
.global printf
.global cr
.syntax unified

.text
TestAsmCall:
PUSH {lr}
/*--------------------------------------*/
/*-------Students write their code here ------------*/
//Load starting values
ldr r0, =0x20001000 // address of number of data points
ldr r1, =0x20001004 // address of x data points
ldr r2, =0x20001008 // address of y data points
ldr r3, =0x2000100C // address temporary value
ldr r4, =0x20001010 // addres of result

// Load values from memory
ldr r0, [r0] // load value of # of data points
ldr r1, [r1] // value of x data points
ldr r2, [r2] // value of y data points
ldr r3, [r3] // value of temporary value
ldr r4, [r4] // value of value of result

//find if its 1, 2 or 4
mov r8, r0 // load value of R0 to R8
sub r8, #1 // subtract 1 from the # of vals
mov r9, #0 // load 0 into R9, this is our temporary register for total
mov r10, #0 // the fraction counter initialized to 0

Loop: // Loop to decide what condition is needed
	cmp r8, #0 // If there is no more data
	beq Exit   // points exit the code

	ldr r3, [r1], #4 //get the x value and adjust to the next
	ldr r5, [r1]     //get the needed x value
	sub r3, r5, r3   // subtract x value from next x val
					 // to get delta x and store at R3

	// same idea but with y values added
	ldr r6, [r2], #4
	ldr r7, [r2] 
	add r6, r6, r7 //delta y stored at R6
	
	// depending on the value give it a condition 
	cmp r3, #1
	// conditionOne if delta x is 1
	beq conditionOne 
	cmp r3, #2
	// conditionTwo if delta x is 2 or
	// conditionThree if delta x is 4
	beq conditionTwo
	bgt conditionThree

conditionOne: //number is (b - a) = 1
	lsr r6, r6, #1 // divide value by 2
	BCS conditionOdd // if odd number it goes to the decimal condition

	add r9, r6 // load value with others to R9
	SUB r8, #1 // Subtract total values by 1
	B Loop // Return to loop

conditionTwo: //number is (b - a) = 2
	add r9, r6 // add result to r9
	SUB r8, #1 // subtract total values
	B Loop // return to loop

conditionThree: //number is (b - a) = 4
	lsl r6, r6, #1 // multiply by 2
	add r9, r6 // add to total
	SUB r8, #1 // subtract total # of vals
	B Loop // return to loop

conditionOdd: // if the dividend is odd
	// the result will be a decimal value
	add r10, #1	// for every odd divident add 1 to the total
	add r9, r6 //add vals to total remp register
	SUB r8, #1 // subtract from total
	B Loop // return to main loop

Exit:
	lsr r10, r10, #1 // divide number of decimal values to get total
	add r9, r10 // add decimal vals to total result
	str r9, [r4] // store total result in r4(required result register)

/*-------Code ends here ---------------------*/

/*-----------------DO NOT MODIFY--------*/
POP {PC}

.data
/*--------------------------------------*/
