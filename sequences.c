#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Take the input make it the firts n, apply the ops
// Make that result the next n and applys the ops again forever
#define MAX_OPERATIONS 100

typedef struct {
    char op[4];   // Operation ("add", "sub", "mul", "div")
    int value;    // Operand
} Operation;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <initial_value>\n", argv[0]);
        return 1;
    }

    int current = atoi(argv[1]);  // Initial value of the sequence
    Operation operations[MAX_OPERATIONS];
    int op_count = 0;  // Number of stored operations

    char command[10];
    int operand;

    while (scanf("%s", command) != EOF) {
        if (strcmp(command, "n") == 0) {
            // Compute the next value in the sequence
            int next_value = current;
            for (int i = 0; i < op_count; i++) {
                if (strcmp(operations[i].op, "add") == 0) {
                    next_value += operations[i].value;
                } else if (strcmp(operations[i].op, "sub") == 0) {
                    next_value -= operations[i].value;
                } else if (strcmp(operations[i].op, "mul") == 0) {
                    next_value *= operations[i].value;
                } else if (strcmp(operations[i].op, "div") == 0) {
                    assert(operations[i].value != 0);  // Ensure no division by zero
                    next_value /= operations[i].value;
                }
            }
            printf("%d\n", next_value);
            current = next_value;  // Update current value
        } else {
            // Read an operator and operand
            if (op_count < MAX_OPERATIONS) {
                scanf("%d", &operand);
                strcpy(operations[op_count].op, command);
                operations[op_count].value = operand;
                op_count++;
            } else {
                fprintf(stderr, "Maximum number of operations reached!\n");
            }
        }
    }

    return 0;
}
