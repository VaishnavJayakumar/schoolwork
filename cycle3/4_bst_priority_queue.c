#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char name[50];
    int priority;
} node;

typedef struct {
    node *heap;
    int size, capacity;
} priorityqueue;

priorityqueue* createqueue(int capacity) {
    priorityqueue *q = (priorityqueue*)malloc(sizeof(priorityqueue));
    if (q == NULL) exit(1);
    q->heap = (node*)malloc(capacity * sizeof(node));
    if (q->heap == NULL) {
        free(q);
        exit(1);
    }
    q->size = 0;
    q->capacity = capacity;
    return q;
}

void swap(node *a, node *b) {
    node temp = *a;
    *a = *b;
    *b = temp;
}

void insert(priorityqueue *q, char name[], int priority) {
    if (q->size == q->capacity) {
        printf("Priority queue is full\n");
        return;
    }
    int i = q->size++;
    strcpy(q->heap[i].name, name);
    q->heap[i].priority = priority;
    while (i > 0 && q->heap[(i - 1) / 2].priority < q->heap[i].priority) {
        swap(&q->heap[i], &q->heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

node deletehighest(priorityqueue *q) {
    node highest = q->heap[0];
    q->heap[0] = q->heap[--q->size];
    int i = 0;
    while (1) {
        int left = 2 * i + 1, right = 2 * i + 2, largest = i;
        if (left < q->size && q->heap[left].priority > q->heap[largest].priority)
            largest = left;
        if (right < q->size && q->heap[right].priority > q->heap[largest].priority)
            largest = right;
        if (largest == i) break;
        swap(&q->heap[i], &q->heap[largest]);
        i = largest;
    }
    return highest;
}

int main() {
    priorityqueue *q = createqueue(100);
    int n, i, category;
    char name[50];
    node customer;

    printf("Enter number of customers: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nEnter customer name: ");
        scanf("%49s", name);
        printf("1. Differently abled\n2. Senior citizen\n3. Defence personnel\n4. Ordinary person\nEnter category: ");
        scanf("%d", &category);
        if (category < 1 || category > 4) {
            printf("Invalid category\n");
            i--;
            continue;
        }
        insert(q, name, 5 - category);
    }

    printf("\nSequence of completion:\n");
    while (q->size > 0) {
        customer = deletehighest(q);
        if (customer.priority == 4)
            printf("%s - Differently abled\n", customer.name);
        else if (customer.priority == 3)
            printf("%s - Senior citizen\n", customer.name);
        else if (customer.priority == 2)
            printf("%s - Defence personnel\n", customer.name);
        else
            printf("%s - Ordinary person\n", customer.name);
    }

    free(q->heap);
    free(q);
    return 0;
}