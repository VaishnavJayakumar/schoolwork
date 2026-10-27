#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int exp;
    int cof;
    struct node *link;
} node;

typedef struct {
    node *head;
} linkedlist;

node *createnode(int given_exp, int given_cof) {
    node *n = malloc(sizeof(node));
    if (n == NULL) {
        printf("createnode failed");
        exit(1);
    }
    n->exp = given_exp;
    n->cof = given_cof;
    n->link = NULL;
    return n;
};

linkedlist *createlist() {
    linkedlist *L = malloc(sizeof(linkedlist));
    if (L == NULL) {
        printf("createlist failed\n");
        exit(1);
    }
    L->head = NULL;
    return L;
}

node *promptnode() {
    node *n = (node *) malloc(sizeof(node));
    int given_exp, given_cof;
    printf("\nEnter exponent: ");
    scanf("%d", &given_exp);
    printf("\nEnter coefficient: ");
    scanf("%d", &given_cof);
    if (n == NULL) {
        printf("createnode failed");
        exit(1);
    }
    n->exp = given_exp;
    n->cof = given_cof;
    n->link = NULL;
    return n;
};

char printnode(node *n) {
    if (n == NULL) {
        printf("[Node is NULL]\n");
        return '\0';
    }
    printf("%dx^%d", n->cof, n->exp);
    return '\0';
}

void display(linkedlist *L) {
    if (L->head == NULL) {
        printf("Empty linked list\n");
        return;
    }
    node *curr = L->head;
    printf("polynomial : ");
    while (curr != NULL) {
        printf("%c + ", printnode(curr));
        curr = curr->link;
    }
    printf("0\n");
}

linkedlist *mergelist(linkedlist *LA, linkedlist *LB) {
    if (LA->head == NULL) {
        LA->head = LB->head;
        free(LB);
        return LA;
    }

    node *curr = LA->head;
    while (curr->link != NULL) {
        curr = curr->link;
    }
    curr->link = LB->head;
    free(LB);
    return LA;
}

void sortList(linkedlist *L) {
    if (!L || !L->head || !L->head->link) {
        return;
    }

    node *sorted = NULL;
    node *curr = L->head;
    while (curr != NULL) {
        node *next_node = curr->link;
        if (sorted == NULL || curr->exp > sorted->exp) {
            curr->link = sorted;
            sorted = curr;
        } else {
            node *search = sorted;
            while (search->link != NULL && search->link->exp > curr->exp) {
                search = search->link;
            }
            curr->link = search->link;
            search->link = curr;
        }
        curr = next_node;
    }
    L->head = sorted;
}

void reduce(linkedlist *L) {
    if (!L || !L->head) {
        return;
    }
    node *curr = L->head;
    while (curr != NULL && curr->link != NULL) {
        if (curr->exp == curr->link->exp) {
            curr->cof += curr->link->cof;
            node *temp = curr->link;
            curr->link = curr->link->link;
            free(temp);
        } else {
            curr = curr->link;
        }
    }
}


void appendnode(linkedlist *L, node *new_node) {
    if (L->head == NULL) {
        L->head = new_node;
        return;
    }
    node *curr = L->head;
    while (curr->link != NULL) {
        curr = curr->link;
    }
    curr->link = new_node;
}

linkedlist *copylist(linkedlist *L) {
    linkedlist *new_list = createlist();
    node *curr = L->head;
    while (curr != NULL) {
        node *new_node = createnode(curr->exp, curr->cof);
        appendnode(new_list, new_node);
        curr = curr->link;
    }
    return new_list;
}

node *multiplynodes(node *n1, node *n2) {
    if (n1 == NULL || n2 == NULL) {
        return NULL;
    }
    int new_exp = n1->exp + n2->exp;
    int new_cof = n1->cof * n2->cof;
    return createnode(new_exp, new_cof);
}

linkedlist *multiplylists(linkedlist *LA, linkedlist *LB) {
    linkedlist *LC = createlist();
    if (!LA || !LB || !LC) {
        return NULL;
    }
    node *currA = LA->head;
    while (currA != NULL) {
        node *currB = LB->head;
        while (currB != NULL) {
            node *new_node = multiplynodes(currA, currB);
            appendnode(LC, new_node);
            currB = currB->link;
        }
        currA = currA->link;
    }
    return LC;
}

int main() {
    linkedlist *A = createlist();
    linkedlist *B = createlist();
    linkedlist *C = createlist();
    int opcode = 0;
    node *opnode = NULL;
    while (1) {
        printf("\n Polynomial Multiplication Using Linked List\n");
        printf("A ");
        display(A);
        printf("B ");
        display(B);
        printf("C ");
        display(C);
        printf("\nSelect action : \
            \n1 append to A\
            \n2 append to B\
            \n3 multiply A and B\
            \n4 exit\
            \n\t\t:");
        scanf("%d", &opcode);

        switch (opcode) {
            case 1:
                opnode = promptnode();
                appendnode(A, opnode);
                break;

            case 2:
                opnode = promptnode();
                appendnode(B, opnode);
                break;

            case 3:
                C = multiplylists(A, B);
                sortList(C);
                reduce(C);
                printf("List A and B multiplied into C\n");
                break;

            case 4:
                printf("\nprogram exiting\n");
                exit(0);
                break;

            default:
                printf("\nInvalid option");
                break;
        }
    }
    printf("\n");
    return 0;
}
