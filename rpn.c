#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node{
    int data;
    struct Node *next;
} Node;


//Stack structurte
typedef struct{
    Node* top;
} Stack;

//Initialize stack, now "s" is a pointer to the top of the stack
void initStack(Stack* s) {
    s->top = NULL;
}

// Check if stack empty
int isEmpty(Stack *s) {
    return s->top == NULL;
}

//push and elment onto the stack
void push(Stack* s, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
}

//pop ab ekenebt from the stack
int pop(Stack* s) {
    if (isEmpty(s)) {
        fprintf(stderr, "Error: Stack underflow\n");
        exit(1);
    }
    Node* temp = s->top;
    int popped = temp->data;
    s->top = s->top->next;
    free(temp);
    return popped;
}

// free the stack
void freeStack(Stack* s) {
    while (!isEmpty(s)) {
        pop(s);
    }
}

//recognize a number
int isDigit(char c) {
    return c >= '0' && c <= '9';
};

// recognize if theres a +/- operator to end the math
int isNumber(const char* token) {
    if (token[0] == '-' || token[0] == '+') {
        return isDigit(token[1]);
    }
    return isDigit(token[0]);
}

//put main function
int main() {
    char input[1000];
    Stack stack;
    initStack(&stack);

    //get input
    fgets(input, sizeof(input), stdin);

    //tokenize input by white space
    char* token = strtok(input, " \t\n");

    //Write main function here
    while (token != NULL) {
        // if the token is a number push to stack
        if (isNumber(token)) {
            int num = atoi(token);
            push(&stack, num);
        }
        // if the token is an operator do the operation and push to stack
        else if (strlen(token) == 1) {
            int b = pop(&stack);
            int a = pop(&stack);
            char op = token[0];
            int result;

            switch (op) {
                case 'p': result = a + b; break;
                case 's': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
                default:
                    printf("Unknown operator: %c\n", op);
                    exit(1);
            }
            push(&stack, result);
        }

        token = strtok(NULL, " \t\n");
    }

    int finalResult = pop(&stack);
    if (!isEmpty(&stack)) {
        fprintf(stderr, "Error: Too many operands\n");
        freeStack(&stack);
        exit(1);
    }
    printf("%d\n", finalResult);

    freeStack(&stack);
    return 0;
}