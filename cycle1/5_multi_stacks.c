#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int top1;
    int top2;
} twostack;

twostack* createstack() {
    twostack* S = (twostack*)malloc(sizeof(twostack));

    if (S == NULL) {
        printf("createstack failed\n");
        exit(1);
    }

    S->top1 = -1;
    S->top2 = MAX;

    return S;
}

void push(twostack* S, int x, int stack_no) {
    if (S->top1 + 1 == S->top2) {
        printf("Stack Overflow\n");
        return;
    }

    if (stack_no == 1) {
        S->data[++S->top1] = x;
        printf("%d pushed into Stack 1\n", x);
    }
    else if (stack_no == 2) {
        S->data[--S->top2] = x;
        printf("%d pushed into Stack 2\n", x);
    }
    else {
        printf("Invalid stack number\n");
    }
}

void pop(twostack* S, int stack_no) {
    if (stack_no == 1) {
        if (S->top1 == -1) {
            printf("Stack 1 Underflow\n");
            return;
        }

        printf("Popped %d from Stack 1\n", S->data[S->top1--]);
    }
    else if (stack_no == 2) {
        if (S->top2 == MAX) {
            printf("Stack 2 Underflow\n");
            return;
        }

        printf("Popped %d from Stack 2\n", S->data[S->top2++]);
    }
    else {
        printf("Invalid stack number\n");
    }
}

void peek(twostack* S, int stack_no) {
    if (stack_no == 1) {
        if (S->top1 == -1) {
            printf("Stack 1 is empty\n");
            return;
        }

        printf("Top of Stack 1 = %d\n", S->data[S->top1]);
    }
    else if (stack_no == 2) {
        if (S->top2 == MAX) {
            printf("Stack 2 is empty\n");
            return;
        }

        printf("Top of Stack 2 = %d\n", S->data[S->top2]);
    }
    else {
        printf("Invalid stack number\n");
    }
}

void display(twostack* S, int stack_no) {
    int i;

    if (stack_no == 1) {
        if (S->top1 == -1) {
            printf("Stack 1 is empty\n");
            return;
        }

        printf("Stack 1 : ");
        for (i = 0; i <= S->top1; i++) {
            printf("%d ", S->data[i]);
        }
        printf("\n");
    }
    else if (stack_no == 2) {
        if (S->top2 == MAX) {
            printf("Stack 2 is empty\n");
            return;
        }

        printf("Stack 2 : ");
        for (i = MAX - 1; i >= S->top2; i--) {
            printf("%d ", S->data[i]);
        }
        printf("\n");
    }
    else {
        printf("Invalid stack number\n");
    }
}

int main() {
    twostack* S = createstack();

    int opcode;
    int stack_no;
    int operand;

    while (1) {
        printf("\n");
        display(S, 1);
        display(S, 2);

        printf("\nSelect action : "
               "\n1 PUSH"
               "\n2 POP"
               "\n3 PEEK"
               "\n4 DISPLAY"
               "\n5 EXIT"
               "\n\t:");

        scanf("%d", &opcode);

        switch (opcode) {
            case 1:
                printf("Enter stack number (1 or 2): ");
                scanf("%d", &stack_no);

                printf("Enter element: ");
                scanf("%d", &operand);

                push(S, operand, stack_no);
                break;

            case 2:
                printf("Enter stack number (1 or 2): ");
                scanf("%d", &stack_no);

                pop(S, stack_no);
                break;

            case 3:
                printf("Enter stack number (1 or 2): ");
                scanf("%d", &stack_no);

                peek(S, stack_no);
                break;

            case 4:
                printf("Enter stack number (1 or 2): ");
                scanf("%d", &stack_no);

                display(S, stack_no);
                break;

            case 5:
                printf("\nprogram exiting\n");
                free(S);
                exit(0);

            default:
                printf("\nInvalid option\n");
                break;
        }
    }

    return 0;
}