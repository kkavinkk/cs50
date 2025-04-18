#include <stdio.h>

//read one int from standard input

//Print everg disisors of the read into from smalllest to largest with a space in between

//print new line after

int main() {
    int num;
    scanf("%d", &num);

    int first = 1;
    for (int i = 1; i <= num; i++) {
        if (num % i == 0) {
            if (!first) {
                printf(" ");
            }
            printf("%d", i);
            first = 0;
        }
    }
    printf("\n");
    return 0;
}