#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node {
    char data;
    struct node *left, *right;
} node;

typedef struct {
    node *root;
} tree;

node* createnode(char value) {
    node *n = (node*)malloc(sizeof(node));
    if (n == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    n->data = value;
    n->left = n->right = NULL;
    return n;
}

tree* createtree() {
    tree *t = (tree*)malloc(sizeof(tree));
    if (t == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    t->root = NULL;
    return t;
}

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

node* createtreefrompostfix(char postfix[]) {
    node *stack[100];
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];
        if (ch == ' ' || ch == '\n')
            continue;
        if (isalnum((unsigned char)ch))
            stack[++top] = createnode(ch);
        else {
            if (top < 1) {
                printf("Invalid expression\n");
                exit(1);
            }
            node *n = createnode(ch);
            n->right = stack[top--];
            n->left = stack[top--];
            stack[++top] = n;
        }
    }
    if (top != 0) {
        printf("Invalid expression\n");
        exit(1);
    }
    return stack[top];
}

void preorder(node *n) {
    if (n != NULL) {
        printf("%c ", n->data);
        preorder(n->left);
        preorder(n->right);
    }
}

void inorder(node *n) {
    if (n != NULL) {
        if (n->left != NULL && n->right != NULL)
            printf("(");
        inorder(n->left);
        printf("%c", n->data);
        inorder(n->right);
        if (n->left != NULL && n->right != NULL)
            printf(")");
    }
}

void postorder(node *n) {
    if (n != NULL) {
        postorder(n->left);
        postorder(n->right);
        printf("%c ", n->data);
    }
}

int main() {
    char infix[100], postfix[100], operators[100];
    int top = -1, j = 0;
    tree *T = createtree();

    printf("Enter a simple arithmetic expression: ");
    
    if (fgets(infix, sizeof(infix), stdin) == NULL) {
        free(T);
        return 1;
    }

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];
        if (ch == ' ' || ch == '\n')
            continue;
        if (isalnum((unsigned char)ch))
            postfix[j++] = ch;
        else if (ch == '(')
            operators[++top] = ch;
        else if (ch == ')') {
            while (top >= 0 && operators[top] != '(')
                postfix[j++] = operators[top--];
            if (top < 0) {
                printf("Invalid expression\n");
                free(T);
                return 1;
            }
            top--;
        } else if (ch == '+' || ch == '-' || ch == '*' ||
                   ch == '/' || ch == '^') {
            while (top >= 0 && operators[top] != '(' &&
                   (precedence(operators[top]) > precedence(ch) ||
                   (precedence(operators[top]) == precedence(ch) && ch != '^')))
                postfix[j++] = operators[top--];
            operators[++top] = ch;
        } else {
            printf("Invalid character in expression\n");
            free(T);
            return 1;
        }
    }

    while (top >= 0) {
        if (operators[top] == '(') {
            printf("Invalid expression\n");
            free(T);
            return 1;
        }
        postfix[j++] = operators[top--];
    }
    postfix[j] = '\0';

    T->root = createtreefrompostfix(postfix);

    printf("\nInfix expression: ");
    inorder(T->root);
    printf("\nPrefix expression: ");
    preorder(T->root);
    printf("\nPostfix expression: ");
    postorder(T->root);
    printf("\n");
    return 0;
}