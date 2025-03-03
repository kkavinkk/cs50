#include <stdio.h>
#include <stdlib.h>

int strToInt(const char *s) {
    // here was can take in a string and returns it int equivilent
    int sum = 0;
    for (; *s !=  '\0'; ++s) {
        int digit = *s - '0';
        sum = sum*10 +digit;
    }
    return sum;
}

void print2DArray(int **mat, int r, int c) {
    //print 2d array of ints with r number of rows
    // and c number of columns
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            printf("%d", mat[i][j]);
        }
        printf("\n")
    }
}

int main(int argc, char **argv) {
    
}