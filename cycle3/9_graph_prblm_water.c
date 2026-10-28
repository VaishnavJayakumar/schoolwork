#include <stdio.h>
#include <stdlib.h>

#define MAX_A 10
#define MAX_B 7
#define MAX_C 4

typedef struct node {
    int a, b, c, visited;
    struct node *parent;
    struct edge *adj;
    struct node *next;
} node;

typedef struct edge {
    node *dest;
    struct edge *next;
} edge;

typedef struct graph {
    node *head;
} graph;

node *state[11][8][5];

node *createnode(int a, int b, int c) {
    node *n = malloc(sizeof(node));
    if (n == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    n->a = a;
    n->b = b;
    n->c = c;
    n->visited = 0;
    n->parent = NULL;
    n->adj = NULL;
    n->next = NULL;
    return n;
}

graph *creategraph(void) {
    graph *g = malloc(sizeof(graph));
    if (g == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    g->head = NULL;
    return g;
}

void insertnode(graph *g, node *n) {
    n->next = g->head;
    g->head = n;
    state[n->a][n->b][n->c] = n;
}

void addedge(node *src, node *dest) {
    edge *e = malloc(sizeof(edge));
    if (e == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    e->dest = dest;
    e->next = src->adj;
    src->adj = e;
}

void pour(int amount[], int capacity[], int i, int j, int result[]) {
    for (int x = 0; x < 3; x++)
        result[x] = amount[x];

    int transfer = amount[i];
    if (transfer > capacity[j] - amount[j])
        transfer = capacity[j] - amount[j];

    result[i] -= transfer;
    result[j] += transfer;
}

graph *buildgraph(void) {
    graph *g = creategraph();

    for (int a = 0; a <= MAX_A; a++) {
        for (int b = 0; b <= MAX_B; b++) {
            for (int c = 0; c <= MAX_C; c++) {
                if (a + b + c == 11)
                    insertnode(g, createnode(a, b, c));
            }
        }
    }

    int capacity[3] = {10, 7, 4};

    for (node *n = g->head; n != NULL; n = n->next) {
        int amount[3] = {n->a, n->b, n->c}, result[3];

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (i == j || amount[i] == 0 || amount[j] == capacity[j])
                    continue;

                pour(amount, capacity, i, j, result);
                node *dest = state[result[0]][result[1]][result[2]];

                if (dest != NULL)
                    addedge(n, dest);
            }
        }
    }
    return g;
}

int isgoal(node *n) {
    return n->b == 2 || n->c == 2;
}

node *bfs(graph *g) {
    node *start = state[0][7][4];
    node *queue[200];
    int front = 0, rear = 0;

    start->visited = 1;
    queue[rear++] = start;

    while (front < rear) {
        node *current = queue[front++];

        if (isgoal(current))
            return current;

        for (edge *e = current->adj; e != NULL; e = e->next) {
            node *nextnode = e->dest;

            if (!nextnode->visited) {
                nextnode->visited = 1;
                nextnode->parent = current;
                queue[rear++] = nextnode;
            }
        }
    }
    return NULL;
}

void printpath(node *goal) {
    if (goal == NULL) {
        printf("No solution exists.\n");
        return;
    }

    node *path[200];
    int count = 0;

    while (goal != NULL) {
        path[count++] = goal;
        goal = goal->parent;
    }

    printf("Solution found!\nState format: (10L, 7L, 4L)\n\n");

    for (int i = count - 1; i >= 0; i--) {
        printf("(%d, %d, %d)", path[i]->a, path[i]->b, path[i]->c);
        if (i > 0)
            printf(" -> ");
        if (i == 0)
            printf("  [Initial state]");
        printf("\n");
    }

    printf("\nNumber of pouring operations: %d\n", count - 1);
}

void displayoperations(node *goal) {
    node *path[200];
    int count = 0;

    while (goal != NULL) {
        path[count++] = goal;
        goal = goal->parent;
    }

    printf("\nPouring sequence:\n");

    for (int i = count - 1; i > 0; i--) {
        node *p = path[i], *q = path[i - 1];
        int before[3] = {p->a, p->b, p->c};
        int after[3] = {q->a, q->b, q->c};
        char *names[] = {"10L", "7L", "4L"};

        for (int s = 0; s < 3; s++) {
            if (before[s] > after[s]) {
                for (int d = 0; d < 3; d++) {
                    if (before[d] < after[d]) {
                        printf("%s -> %s\n", names[s], names[d]);
                        break;
                    }
                }
                break;
            }
        }
    }
}

int main(void) {
    graph *g = buildgraph();

    printf("Initial state: (0, 7, 4)\n");
    printf("Goal: 7L or 4L container has exactly 2L\n\n");

    node *goal = bfs(g);

    if (goal != NULL) {
        printpath(goal);
        displayoperations(goal);
    } else {
        printf("No solution exists.\n");
    }

    return 0;
}