#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// start with check digit

// multiple the first digit to the left by 2, if its bigger than 10 sub 9 and add

// add the next digit to the number w not mods

// alternate the add proccess w the sub 9 process to the end

// multiply the sum by 9 and divide 10, if the result is the same as the check digit
// it is valid


int main() {
    int ch;
    int reversed = 0;
    int digitCount = 0;

    //read input char by char until a non digit
    while ((ch = getchar()) >= '0' && ch <= '9') {
        int digit = ch - '0';
        reversed = reversed * 10  + digit;
        digitCount++;
    }

    //not digits
    if (digitCount == 0) {
        printf("Valid\n");
        return 0;
    }

    int sum = 0;
    int position = 0;

    int checkDigit = reversed % 10; // right most digit of reversed is check digit
    reversed /= 10;

    while (reversed > 0) {
        int digit = reversed % 10;

        if (position % 2 == 0) {
            digit *= 2;
            if (digit >= 10) digit -= 9;
        }

        sum += digit;
        reversed /= 10;
        position++;
    }

    sum *= 9;
    int newCheck = sum % 10;

    if (newCheck == checkDigit) {
        printf("Valid\n");
    } else {
        printf("Invalid\n");
    }

    return 0;
}

