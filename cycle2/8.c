#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* link;
} node;

node* createnode(int given_value) {
    node* n = (node*)malloc(sizeof(node));

    if (n == NULL) {
        printf("createnode failed\n");
        exit(1);
    }

    n->data = given_value;
    n->link = NULL;

    return n;
}

typedef struct {
    node* head;
} linkedlist;

linkedlist* createlist() {
    linkedlist* L = (linkedlist*)malloc(sizeof(linkedlist));

    if (L == NULL) {
        printf("createlist failed\n");
        exit(1);
    }

    L->head = NULL;
    return L;
}

void insertnode(linkedlist* L, int given_value, int pos) {
    if (pos < 0) {
        printf("Invalid position\n");
        return;
    }

    if (pos == 0) {
        prependnode(L, given_value);
        printf("Inserted %d at position %d\n", given_value, pos);
        return;
    }

    if (L->head == NULL) {
        printf("Position out of bounds\n");
        return;
    }

    node* curr = L->head;

    for (int i = 0; i < pos - 1; i++) {
        curr = curr->link;

        if (curr == L->head) {
            printf("Position out of bounds\n");
            return;
        }
    }

    node* new_node = createnode(given_value);

    new_node->link = curr->link;
    curr->link = new_node;

    printf("Inserted %d at position %d\n", given_value, pos);
}

void deletenode(linkedlist* L, int pos) {
    if (L->head == NULL) {
        printf("No elements to delete\n");
        return;
    }

    if (pos < 0) {
        printf("Invalid position\n");
        return;
    }

    if (pos == 0) {
        node* temp = L->head;

        if (L->head->link == L->head) {
            L->head = NULL;
            free(temp);
            printf("Element index 0 deleted\n");
            return;
        }

        node* last = L->head;

        while (last->link != L->head) {
            last = last->link;
        }

        L->head = L->head->link;
        last->link = L->head;

        free(temp);

        printf("Element index 0 deleted\n");
        return;
    }

    node* prev = L->head;
    node* curr = L->head->link;

    for (int i = 1; i < pos; i++) {
        if (curr == L->head) {
            printf("Invalid position %d\n", pos);
            return;
        }

        prev = curr;
        curr = curr->link;
    }

    if (curr == L->head) {
        printf("Invalid position %d\n", pos);
        return;
    }

    prev->link = curr->link;
    free(curr);

    printf("Element index %d deleted\n", pos);
}

void deletevalue(linkedlist* L, int val) {
    if (L->head == NULL) {
        printf("Empty linked list\n");
        return;
    }

    int flag = 0;
    int pos = 0;

    node* curr = L->head;
    node* prev = NULL;

    do {
        if (curr->data == val) {
            flag = 1;

            /* Only one node exists */
            if (curr == L->head && curr->link == L->head) {
                free(curr);
                L->head = NULL;
                printf("Element index %d deleted\n", pos);
                return;
            }

            /* Deleting head */
            if (curr == L->head) {
                node* last = L->head;

                while (last->link != L->head) {
                    last = last->link;
                }

                L->head = L->head->link;
                last->link = L->head;

                free(curr);
                curr = L->head;
            }
            else {
                prev->link = curr->link;
                free(curr);
                curr = prev->link;
            }

            printf("Element index %d deleted\n", pos);

            /* Restart traversal after deleting head */
            if (curr == L->head) {
                prev = NULL;
            }
        }
        else {
            prev = curr;
            curr = curr->link;
            pos++;
        }

    } while (curr != L->head);

    if (!flag) {
        printf("No elements with value %d were deleted\n", val);
    }
}

void display(linkedlist* L) {
    if (L->head == NULL) {
        printf("\nEmpty circular linked list\n");
        return;
    }

    node* curr = L->head;

    printf("\nCircular linked list: ");

    do {
        printf("%d --> ", curr->data);
        curr = curr->link;
    } while (curr != L->head);

    printf("(head)\n");
}

int main() {
    linkedlist* A = createlist();

    int opcode;
    int operand;
    int operand2;

    while (1) {
        display(A);

        printf("\nSelect action:");
        printf("\n1. Insert node at a position");
        printf("\n2. Delete node at a position");
        printf("\n3. Delete node by a particular value");
        printf("\n4. Exit");
        printf("\n\t:");

        scanf("%d", &opcode);

        switch (opcode) {

            case 1:
                printf("\nNew node position: ");
                scanf("%d", &operand2);

                printf("\nNew node value: ");
                scanf("%d", &operand);

                insertnode(A, operand, operand2);
                break;

            case 2:
                printf("\nDeleting node position: ");
                scanf("%d", &operand);

                deletenode(A, operand);
                break;

            case 3:
                printf("\nDeleting node of value: ");
                scanf("%d", &operand);

                deletevalue(A, operand);
                break;

            case 4:
                printf("\nProgram exiting\n");
                exit(0);

            default:
                printf("\nInvalid option\n");
                break;
        }
    }

    return 0;
}