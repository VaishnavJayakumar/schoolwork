#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int size;
    int allocated;
    struct node *prev;
    struct node *next;
} node;

node* create_node(int size, int allocated) {
    node* n = (node*)malloc(sizeof(node));

    if (n == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    n->size = size;
    n->allocated = allocated;
    n->prev = NULL;
    n->next = NULL;

    return n;
}

typedef struct {
    node* head;
} memory;

memory* create_memory() {
    memory* m = (memory*)malloc(sizeof(memory));

    if (m == NULL) {
        printf("Memory creation failed\n");
        exit(1);
    }

    m->head = NULL;
    return m;
}

void insert_block(memory* m, int size, int allocated) {
    node* n = create_node(size, allocated);

    if (m->head == NULL) {
        m->head = n;
        return;
    }

    node* curr = m->head;

    while (curr->next != NULL)
        curr = curr->next;

    curr->next = n;
    n->prev = curr;
}

void display(memory* m) {
    node* curr = m->head;
    int block = 1;

    printf("\nMemory Blocks:\n");
    printf("--------------------------------\n");

    while (curr != NULL) {
        printf("Block %d : Size = %d, %s\n",
               block,
               curr->size,
               curr->allocated ? "Allocated" : "Free");

        curr = curr->next;
        block++;
    }

    printf("--------------------------------\n");
}

void garbage_collection(memory* m) {
    node* curr = m->head;

    while (curr != NULL) {
        if (!curr->allocated) {
            node* next = curr->next;

            /* Merge consecutive free blocks */
            while (next != NULL && !next->allocated) {
                curr->size += next->size;
                curr->next = next->next;

                if (next->next != NULL)
                    next->next->prev = curr;

                free(next);
                next = curr->next;
            }
        }

        curr = curr->next;
    }

    printf("\nGarbage collection completed.\n");
}

void compaction(memory* m) {
    node* curr = m->head;
    node* last_allocated = NULL;
    int free_size = 0;

    while (curr != NULL) {
        node* next = curr->next;

        if (curr->allocated) {
            if (last_allocated == NULL) {
                m->head = curr;
                curr->prev = NULL;
            } else {
                last_allocated->next = curr;
                curr->prev = last_allocated;
            }

            last_allocated = curr;
        } else {
            free_size += curr->size;
            free(curr);
        }

        curr = next;
    }

    if (last_allocated != NULL)
        last_allocated->next = NULL;

    /* Create one free block after all allocated blocks */
    if (free_size > 0) {
        node* free_block = create_node(free_size, 0);

        if (last_allocated == NULL) {
            m->head = free_block;
        } else {
            last_allocated->next = free_block;
            free_block->prev = last_allocated;
        }
    }

    printf("\nCompaction completed.\n");
}

int main() {
    memory* m = create_memory();

    int n, size, status;

    printf("Enter number of memory blocks: ");
    scanf("%d", &n);

    printf("\nEnter block size and status:\n");
    printf("1 = Allocated, 0 = Free\n");

    for (int i = 0; i < n; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d %d", &size, &status);

        insert_block(m, size, status);
    }

    printf("\nInitial memory:");
    display(m);

    garbage_collection(m);

    printf("\nAfter Garbage Collection:");
    display(m);

    compaction(m);

    printf("\nAfter Compaction:");
    display(m);

    return 0;
}