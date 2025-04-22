#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Create a different function for each type of mutatio??
#define MAX_SIZE 100

typedef struct IntSet {
    int data[MAX_SIZE];
    int size;
} IntSet;

// Helper: check if value is in set
int contains(IntSet *set, int value) {
    for (int i = 0; i < set->size; i++) {
        if (set->data[i] == value) return 1;
    }
    return 0;
}

// a <targ> <int> - adding an int to a set
void a(IntSet* set, int value) {
    set->data[set->size] = value;
    set->size++;
}

// r <targ> <int> - remove an int from a set
void r(IntSet* set, int value) {
    for (int i = 0; i < set->size; i++) {
        if (set->data[i] == value) {
            for (int j = i; j < set->size - 1; j++) {
                set->data[j] = set->data[j + 1];
            }
            set->size--;
            return;
        }
    }
}


// p <targ> - print out a set in sorted order
void p(IntSet *set) {
    if (set->size == 0) {
        return;
    }
    //sorting
    for (int i = 0; i < set->size - 1; i++) {
        //j is the counter for the inner loop
        for (int j = 0; j < set->size - i - 1; j++) {
            if (set->data[j] > set->data[j + 1]) {
                //swap
                int temp = set->data[j];
                set->data[j] = set->data[j + 1];
                set->data[j + 1] = temp;
            }
        }
    }
    //printing
    for (int i = 0; i < set->size; i++) {
        // Only print if it's the first element or different from the previous one
        if (i == 0 || set->data[i] != set->data[i - 1]) {
            printf("%d", set->data[i]);
            // Check if the next different element exists to print space
            int j = i + 1;
            while (j < set->size && set->data[j] == set->data[i]) j++;
            if (j < set->size) printf(" ");
        }
    }
    printf("\n");
}

// u - set union and print
void u(IntSet *a, IntSet *b) {
    IntSet result = { .size = 0 };

    // add fromt set a
    for (int i = 0; i < a->size; i++) {
        result.data[result.size++] = a->data[i];
    }

    //add new elements from set b
    for (int i = 0; i < b->size; i++) {
        if (!contains(&result, b->data[i])) {
            result.data[result.size++] = b->data[i];
        }
    }

    p(&result);
}

// i - set intersection and print
void i(IntSet *a, IntSet *b) {
    IntSet result = { .size = 0 };

    for (int i = 0; i < a->size; i++) {
        if (contains(b, a->data[i])) {
            result.data[result.size++] = a->data[i];
        }
    }
    p(&result);
}


// Main function
int main() {
    //two sets that will be operated on
    IntSet x = { .size = 0 };
    IntSet y = { .size = 0 };
    
    char line[256];
    while(fgets(line, sizeof(line), stdin)) {

        // tokenize
        char* cmd = strtok(line, " \t\r\n");
        if (cmd == NULL) continue;

        // if q - quit the program
        if (strcmp(cmd, "q") == 0) {
            break;
        }
        // else if - a or r
        else if (strcmp(cmd, "a") == 0 || strcmp(cmd, "r") == 0) {
            // detect if its already in the set
            char* targ = strtok(NULL, " \t\r\n");
            char* val_str = strtok(NULL, " \t\r\n");
            if (!targ || !val_str) continue;
            int val = atoi(val_str);

            IntSet* target = (*targ == 'x') ? &x : &y;

            if (strcmp(cmd, "a") == 0) {
                a(target, val);
            } else {
                r(target, val);
            }
        } 
        // else if - p
        else if (strcmp(cmd, "p") == 0) {
            char* targ = strtok(NULL, " \t\r\n");
            if (!targ) continue;
            IntSet* target = (*targ == 'x') ? &x : &y;
            p(target);
        }
        // else if - u
        else if (strcmp(cmd, "u") == 0) {
            u(&x, &y);
        }
        // else if - i
        else if (strcmp(cmd, "i") == 0) {
            i(&x, &y);
        }
    }
    return 0;
}