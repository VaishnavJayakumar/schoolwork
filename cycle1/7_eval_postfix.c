#include <stdio.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int top;
} Stack;

void push(Stack *s, int value) {
    s->data[++s->top] = value;
}

int pop(Stack *s) {
    return s->data[s->top--];
}

int evaluatePostfix(char postfix[]) {
    Stack s;
    s.top = -1;

    int i = 0;
    int a, b, result;

    while (postfix[i] != '\0') {

        // If operand, push it onto the stack
        if (isdigit(postfix[i])) {
            push(&s, postfix[i] - '0');
        }

        // If operator, pop two operands and perform operation
        else {
            b = pop(&s);
            a = pop(&s);

            switch (postfix[i]) {
                case '+':
                    result = a + b;
                    break;

                case '-':
                    result = a - b;
                    break;

                case '*':
                    result = a * b;
                    break;

                case '/':
                    result = a / b;
                    break;

                case '%':
                    result = a % b;
                    break;
            }

            push(&s, result);
        }

        i++;
    }

    return pop(&s);
}

int main() {
    char postfix[MAX];

    printf("Enter postfix expression: ");
    scanf("%s", postfix);

    printf("Result = %d\n", evaluatePostfix(postfix));

    return 0;
}