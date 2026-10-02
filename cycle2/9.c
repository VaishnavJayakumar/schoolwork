#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int size;
    int allocated;
    struct node *link;
} node;

node* createNode(int size) {
    node *n = (node*)malloc(sizeof(node));

    if (n == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    n->size = size;
    n->allocated = 0;
    n->link = NULL;

    return n;
}

void insert(node **head, int size) {
    node *n = createNode(size);

    if (*head == NULL) {
        *head = n;
        return;
    }

    node *temp = *head;

    while (temp->link != NULL)
        temp = temp->link;

    temp->link = n;
}

void display(node *head) {
    node *temp = head;
    int i = 1;

    printf("\nMemory Blocks:\n");

    while (temp != NULL) {
        printf("Block %d: Size = %d, %s\n",
               i,
               temp->size,
               temp->allocated ? "Allocated" : "Free");

        temp = temp->link;
        i++;
    }
}

void firstFit(node *head, int processSize) {
    node *temp = head;

    while (temp != NULL) {
        if (!temp->allocated && temp->size >= processSize) {
            temp->allocated = 1;
            printf("Process of size %d allocated using First-Fit\n",
                   processSize);
            return;
        }

        temp = temp->link;
    }

    printf("Process of size %d could not be allocated\n", processSize);
}

void bestFit(node *head, int processSize) {
    node *temp = head;
    node *best = NULL;

    while (temp != NULL) {
        if (!temp->allocated && temp->size >= processSize) {
            if (best == NULL || temp->size < best->size)
                best = temp;
        }

        temp = temp->link;
    }

    if (best != NULL) {
        best->allocated = 1;
        printf("Process of size %d allocated using Best-Fit\n",
               processSize);
    } else {
        printf("Process of size %d could not be allocated\n",
               processSize);
    }
}

void worstFit(node *head, int processSize) {
    node *temp = head;
    node *worst = NULL;

    while (temp != NULL) {
        if (!temp->allocated && temp->size >= processSize) {
            if (worst == NULL || temp->size > worst->size)
                worst = temp;
        }

        temp = temp->link;
    }

    if (worst != NULL) {
        worst->allocated = 1;
        printf("Process of size %d allocated using Worst-Fit\n",
               processSize);
    } else {
        printf("Process of size %d could not be allocated\n",
               processSize);
    }
}

void freeList(node *head) {
    node *temp;

    while (head != NULL) {
        temp = head;
        head = head->link;
        free(temp);
    }
}

int main() {
    node *head = NULL;
    int n, i, size;
    int choice, processSize;


    printf("Enter number of memory blocks: ");
    scanf("%d", &n);

    printf("Enter sizes of memory blocks:\n");

    for (i = 0; i < n; i++) {
        scanf("%d", &size);
        insert(&head, size);
    }

    while (1) {
        display(head);
        printf("\n--- Memory Allocation ---\n");
        printf("1. First-Fit\n");
        printf("2. Best-Fit\n");
        printf("3. Worst-Fit\n");
        printf("4. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter process size: ");
                scanf("%d", &processSize);
                firstFit(head, processSize);
                break;

            case 2:
                printf("Enter process size: ");
                scanf("%d", &processSize);
                bestFit(head, processSize);
                break;

            case 3:
                printf("Enter process size: ");
                scanf("%d", &processSize);
                worstFit(head, processSize);
                break;

            case 4:
                freeList(head);
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}