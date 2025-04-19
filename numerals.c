#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// rule 1: if a numaral is placed after the large or equal numeral
// then the value is added to the total

// rule 2: if the numeal is added after the smalled numeral then it is subtracted

// Have a dictionary with corresponding values
int romanValue(char c) {
    switch (c) {
        case 'I' : return 1;
        case 'V' : return 5;
        case 'X' : return 10;
        case 'L' : return 50;
        case 'C' : return 100;
        case 'D' : return 500;
        case 'M' : return 1000;
        default:  return 0;
    }
}



int main() {
    size_t max_size = 10000001;
    char *roman = malloc(max_size);

    if (fgets(roman, max_size, stdin) == NULL) {
        printf("0\n");
        free(roman);
        return 1;
    }

    // Remove newline if present
    size_t len = strlen(roman);
    if (roman[len - 1] == '\n') {
        roman[len - 1] = '\0';
        len--;
    }

    //logic for conversion
    int total = 0;
    for (size_t i = 0; i < len; i++) {
        int current = romanValue(roman[i]);
        int next = romanValue(roman[i + 1]);

        if (next > current) {
            total -= current;
        } else {
            total += current;
        }
    }

    printf("%d\n", total);
    free(roman);
    return 0;
} 
