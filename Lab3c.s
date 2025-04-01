/*Author - Lab Tech. Last edited on Jan 14, 2022 */
/*-----------------DO NOT MODIFY--------*/
.global Display
.global printf
.global cr
.extern value
.extern getstring
.syntax unified

.text
Display:
/*-----------------Students write their subroutine here--------------------*/

   //Save registers
   push {r0-r7, lr}

   ldr r4, [sp, #36]    // load # of entries to R4
   ldr r5,  [sp, #40]   // load array pointer to r5

   //Displau first general exit message
   ldr r0, =endprompt
   bl printf
   bl cr

   //message for howmany entries
   ldr r0, =Entries
   bl printf
   bl cr

   //show how many entries
   mov r0, r4
   bl value
   bl cr

   //show sorted list message
   ldr r0, =sorted_msg
   bl printf
   bl cr

   mov r6, r4  //loop counter for number of entries

//loop for each number ot be printed
DisplayLoop:

   cmp r6, #0     //if no more vals exit
   beq End_Code

   ldr r0, [r5], #4  //load current number and move to next
   bl value
   BL cr

   sub r6, #1     //increment loop counter and rerun
   b DisplayLoop

End_Code:
   pop {r0-r7, pc}   //restor registers and return

/*-------Code ends here ---------------------*/

/*-----------------Add your strings here in the data section--------*/
.data
endprompt:
.string "The numbers are sorted with bubble sort algorithm"
Entries:
.string "The number of entries was"
sorted_msg:
.string "sorted from smallest to biggest, the numbers are:"

