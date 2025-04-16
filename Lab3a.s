/*Author - Lab Tech. Last edited on Jan 14, 2022 */
/*-----------------DO NOT MODIFY--------*/
.global Welcomeprompt
.global printf
.global cr
.extern value
.extern getstring
.syntax unified

.text
Welcomeprompt:
/*-----------------Students write their subroutine here--------------------*/

// Save registers to the stack (callee preservation)
   push {lr}
   push {r0-r9}
   mov r7, r0
   bl cr
   // Display welcome message
   ldr r0, =Welcome_String
   bl printf
   bl cr

Prompt_Entries:
   // prom for # of entries between 3 and 11
   ldr r0, =Entries_Prompt
   bl printf
   bl cr

   bl getstring  // Get user input for number of entries
   mov r6, r0
   mov r9, r0
   bl value //print val

   // make sure number is between 3 and 11
   cmp r6, #3
   blt Invalid_Entry_Min //go to min error if val too small
   cmp r6, #10
   bgt Invalid_Entry_Max //go to max error if val too big

   //if ok go to get limits
   b PromptLimits

//number of vals too small
Invalid_Entry_Min:
   // Display error message for too few entries
   ldr r0, =Entry_to_low
   bl printf
   bl cr

   b Prompt_Entries // got back to number of entries

//number of entries too large
Invalid_Entry_Max:
   // Display error message for too many entries
   ldr r0, =Entry_to_high
   bl printf
   bl cr

   b Prompt_Entries //go back to number of entires

//get upper and lower limits
PromptLimits:
   // Prompt for lower limit
   ldr r0, =Lower_Limit_Prompt
   bl printf
   bl cr
   bl getstring
   mov r4, R0    // Store lower limit in R4
   bl value
   bl cr

   //prompt for upper limit
   ldr r0, =Upper_Limit_Prompt
   bl printf
   bl cr
   bl getstring
   mov r5, r0    // Store upper limit in R5
   bl value

   // Make sur eupper limit is greater than lower limit
   cmp r4, r5
   bge Invalid_Limits //if wrong go to invalid limits

   b Prompt_Numbers //if of carry on


Invalid_Limits:
   // Display error message for invalid limits
   bl cr
   ldr r0, =Bad_limits_prompt
   bl printf
   bl cr

   b PromptLimits //go back to getting limits

//loop for prompting required number of values
Prompt_Numbers:
   ldr r0, =NumberPrompt
   bl printf
   //bl cr

   // Compare the values to 1. if equal, all numbers have been entered
   cmp r6, #1 
   beq Last_Number_Entry
   //bl cr

//loop for checking numbers, if withing range
NumberLoop:
   bl getstring
   mov r8, r0 //store value in r8
   bl value
   cmp r8, r4 //check to see if valid
   blt Invalid_Number //if invalid  go to invalid nums

   cmp r8, r5
   bgt Invalid_Number

   str r8, [r7], #4  // Store number at [R1], then increment R1 by 4 to get correct number of entries
   sub r6, #1   // Increment counter
   b Prompt_Numbers // go back to number prompt

Invalid_Number:
   // Display error message for invalid number
   ldr r0, =number_not_inRange
   bl printf
   bl cr
   b NumberLoop

//enter final number
Last_Number_Entry:
   // Prompt for the last number
   bl cr
   ldr r0, =final_number_prompt  // load final entry
   bl printf
   bl cr
   bl getstring //get final num

   cmp r0, r4
   blt Invalid_Number //go back to invalid if bad

   cmp r0, r5
   bgt Invalid_Number //go back to bad number

   str r0, [r7]
   bl value
   bl cr

   /*THIS  MIGHT NEED TO BE #44*/
   str r9, [sp, 44] //put these one stack pointer

Exit:
   pop {r0-r9} //pop used registers
   pop {pc}    //pop pc

/*-------Code ends here ---------------------*/

/*-----------------Add your strings here in the data section--------*/
.data
Welcome_String:       .string "Welcome to ECE 212 Bubble Sorting Program:\r\n"

Entries_Prompt:       .string "Please enter the number of entries (3min-10max):\r\n"

Entry_to_low:  .string "Invalid entry, Please enter more than 2 entries\r\n"

Entry_to_high:  .string "Invalid entry, Please enter less than 11 entries\r\n"

Lower_Limit_Prompt:    .string "Please enter the lower limit:\r\n"

Upper_Limit_Prompt:    .string "Please enter the upper limit:\r\n"

Bad_limits_prompt:    .string "Error. Please enter the lower and upper limit again\r\n"

NumberPrompt:        .string "Please enter a number:\r\n"

final_number_prompt:    .string "Please enter the final number:\r\n"

number_not_inRange:    .string "Invalid!!! Number entered is not within the range\r\n"





