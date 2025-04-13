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
// Part 1 Register Indirect With Offset
ldr r10, =0x20001000 // load address for size of array
ldr r10, [r10] // load size of array

ldr r0,=0x20001004 // address for first value of first array
ldr r0, [r0] // load value of first array

ldr r1, =0x20001008 // address of second array
ldr r1, [r1] // value of first array

// add to thhe inital value which increments the value of the array
ldr r3,[r0]  // first value of first array
ldr r4,[r0, #4]  // second value of first array
ldr r5,[r0, #8]  // third value of first array

// add to thhe inital value which increments the value of the array
ldr r6, [r1] // first value of second array
ldr r7, [r1, #4] // second value of second array
ldr r8, [r1, #8] // third value of second array

ldr r9, =0x2000100C // address for storing result of indirect offset method
ldr r9, [r9] // load the value of ind offset

ADD r3, r6 // add first of array 1 to first of array 2
ADD r4, r7 // add second of array 1 to second of array 2
ADD r5, r8 // add third of array 1 to third of array 2

str r3, [r9] // store first valls in r3
str r4, [r9, #4] // store second val in r4 and Increment
str r5, [r9, #8] // store third val in r4 and Increment

// Part 2 Indexed Register Indirect Method
ldr r9, =0x20001010 // load adress of result for Indexed Register Indirect
ldr r9, [r9] // load val of r9
mov r5, #0 // load 0 into r5

loopTwo:
    ldr r3, [r0, r5] // add values of r5 and r0 and load in r3
    ldr r4, [r1, r5] // add values of r5 and r1 and load in r4

    add r3, r3, r4 // add values of r3 & r4, store in r3
    str r3, [r9, r5] // add vals of r9 and r5, store in r3

    add r5, r5, #4 //shift index of r5

    sub r10, r10, #1 // subtract 1 from r10 and store in r10
    cmp r10, #0 // check if val of r10 is 0
    bgt loopTwo // if not 0 run loop
    beq exitTwo // exit if 0

exitTwo:

// Part 3 Post Increment Register Indirect
ldr r9, =0x20001014 // load adress of result for Indexed Register Indirect
ldr r9, [r9] // load the value of address

ldr r10, =0x20001000 //  load address of array size
ldr r10, [r10] // load array size

Loop:
	ldr r3, [r0], #4 // shift val of r0 by 4 and str in r3
    ldr r4, [r1], #4 // shift val of r1 by 4 and str in r4

    add r3, r3, r4 // add r4 to r3 and store in r3
    str r3, [r9], #4 // add 4 to value of r9 and stor in r3

    sub r10, r10, #1 // subtract size of array by 1 and store in r10
    cmp r10, #0 // check if temp size of array is 0
    bgt Loop // if not 0 loop again
    beq Exit // exit loop if 0

Exit:



































/*-------Code ends here ---------------------*/

/*-----------------DO NOT MODIFY--------*/
POP {PC}

.data
/*--------------------------------------*/
