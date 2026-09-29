#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

typedef struct {
    char arr[MAX];
    int top;
} Stack;

void initialize(Stack *s) {
    s->top = -1;
}

void push(Stack *s, char x) {
    if (s->top == MAX - 1) {
        printf("Stack Overflow\n");
        return;
    }

    s->arr[++s->top] = x;
}

char pop(Stack *s) {
    if (s->top == -1) {
        return '\0';
    }

    return s->arr[s->top--];
}

char peek(Stack *s) {
    if (s->top == -1) {
        return '\0';
    }

    return s->arr[s->top];
}

int precedence(char op) {
    if (op == '^')
        return 3;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return 0;
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' ||
            ch == '*' || ch == '/' || ch == '^');
}

void infixToPostfix(char infix[], char postfix[]) {
    Stack s;
    initialize(&s);

    int i = 0;
    int j = 0;
    char ch;

    while (infix[i] != '\0') {
        ch = infix[i];

        // If operand, add directly to postfix
        if (isalnum(ch)) {
            postfix[j++] = ch;
        }

        // If opening parenthesis, push it
        else if (ch == '(') {
            push(&s, ch);
        }

        // If closing parenthesis, pop until '('
        else if (ch == ')') {
            while (peek(&s) != '(' && s.top != -1) {
                postfix[j++] = pop(&s);
            }

            if (peek(&s) == '(')
                pop(&s);
        }

        // If operator
        else if (isOperator(ch)) {
            while (s.top != -1 &&
                   peek(&s) != '(' &&
                   precedence(peek(&s)) >= precedence(ch)) {
                postfix[j++] = pop(&s);
            }

            push(&s, ch);
        }

        i++;
    }

    // Pop remaining operators
    while (s.top != -1) {
        postfix[j++] = pop(&s);
    }

    postfix[j] = '\0';
}

int main() {
    char infix[MAX];
    char postfix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}