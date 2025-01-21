#include <stdio.h>
/*
int main() {
    // Notes on division in C
    // Division between two ints is an int
    printf("%b\n", 5);
}
*/

int print_binary(unsigned int x) {
    if (x == 0) {
        printf("0");
        return 0;
    }
    int curPow = 1;
    while (curPow <= x) {
        curPow = curPow*2;
    }
    curPow = curPow/2;
    while (x > 0) {
        if (curPow <= x) {
            printf("1");
            x = x - curPow;
        }
        else {
            printf("0");
        }
        curPow = curPow/2;
    }
    printf("\n");
}

int main() {
    print_binary(5);
    print_binary(10);
    print_binary(43821);
}