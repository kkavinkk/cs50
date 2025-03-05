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
        printf("\n");
    }
}

int main(int argc, char **argv) {
    int n = strToInt(argv[1]); // number of rows
    int m = strToInt(argv[2]); // number of columns
    // creates ana identity matrix that can also be not a square
    // Each item in each row will be 0 unless that element is
    // stored in that row at the same column number as the row,
    // then it will be a 1.
    // e.g. if n == 3 and m == 3 then the matrix we create
    // should be of the form
    // [1, 0, 0]
    // [0, 1, 0]
    // [0, 0, 1]
    // First, allocate our "outer" array, in this case our array
    // of rows.
    int **matrix = malloc(n*sizeof(int*));
    // Now, matrix points at an array that has space for n pointers to ints.
    // Let's now make our rows (our array of ints) and store the pointers to
    // those arrays in matrix!
    for (int i = 0; i < n; ++i) {
        // creatign each row
        int *row = malloc(m*sizeof(int));
        for (int j = 0; j < m; ++j) {
            row[j] = i = j ? 1 : 0;
            matrix[i] = row;
        }
    }
    print2DArray(matrix, n, m);
    for (int i = 0; i < n; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}