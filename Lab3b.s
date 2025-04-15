/*Author - Lab Tech. Last edited on Jan 14, 2022 */
/*-----------------DO NOT MODIFY--------*/
.global Sort
.global printf
.global cr
.extern value
.extern getstring
.syntax unified

.text
Sort:
/*-----------------Students write their subroutine here--------------------*/

push {r0-r7, lr} //push required registers onto stack

   ldr r1, [sp, #36] //load the numebr of elements
   mov r3, r0


sort:
   mov r4, r1  //outer loop counter
   sub r4, #1  //increment the counter each pass

main_loop:
   //check if loop counter is zero then exit
   cmp r4, #0
   beq exit

   mov r5, r4  //set loop counter
   mov r6, r3  //start of loop

inner_loop:
    //load 2 elements
    ldr r7, [r6]           // load n element
    ldr r2, [r6, #4]       // load n+1 element

    //check if swap needed
    cmp r7, r2    
    ble no_swap

    //swap the two numbers
    str r2, [r6]           //store n+1 at n
    str r7, [r6, #4]       //store n at n+1

no_swap:
   /* Move pointer and update inner counter */
   add r6, #4          //move pointer to next element
   sub r5, #1          //decrement inner loop counter
   
   //check value with loop limit
   cmp r5, #0
   bgt inner_loop //if not go to inner loop

   sub r4, #1     //decrement outter loop counter
   b main_loop    //back to outter loop

//exit
exit:
   pop {r0-r7, pc}   //restore registers and return



/*-------Code ends here ---------------------*/

/*-----------------Add your strings here in the data section--------*/
.data

