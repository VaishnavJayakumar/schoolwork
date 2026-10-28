#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct node {
    int data, visited;
} node;

typedef struct graph {
    node* nodes[MAX];
    int adj[MAX][MAX], count;
} graph;

node* createnode(int value) {
    node* n = (node*)malloc(sizeof(node));
    if (n == NULL) {
        printf("Error at node allocation\n");
        exit(1);
    }
    n->data = value;
    n->visited = 0;
    return n;
}

graph* creategraph() {
    graph* G = (graph*)malloc(sizeof(graph));
    if (G == NULL) {
        printf("Error at graph allocation\n");
        exit(1);
    }
    G->count = 0;
    for (int i = 0; i < MAX; i++) {
        G->nodes[i] = NULL;
        for (int j = 0; j < MAX; j++)
            G->adj[i][j] = 0;
    }
    return G;
}

void insertnode(graph* G, int value) {
    if (G->count >= MAX) {
        printf("Graph is full\n");
        return;
    }
    G->nodes[G->count++] = createnode(value);
}

void insertedge(graph* G, int u, int v) {
    if (u < 0 || u >= G->count || v < 0 || v >= G->count) {
        printf("Invalid vertex\n");
        return;
    }
    G->adj[u][v] = G->adj[v][u] = 1;
}

void displaygraph(graph* G) {
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < G->count; i++) {
        for (int j = 0; j < G->count; j++)
            printf("%d ", G->adj[i][j]);
        printf("\n");
    }
}

void BFS(graph* G, int start) {
    if (start < 0 || start >= G->count) {
        printf("Invalid starting vertex\n");
        return;
    }

    int queue[MAX], front = 0, rear = 0;

    for (int i = 0; i < G->count; i++)
        G->nodes[i]->visited = 0;

    G->nodes[start]->visited = 1;
    queue[rear++] = start;
    printf("BFS Traversal: ");

    while (front < rear) {
        int current = queue[front++];
        printf("%d ", G->nodes[current]->data);

        for (int i = 0; i < G->count; i++) {
            if (G->adj[current][i] == 1 && G->nodes[i]->visited == 0) {
                G->nodes[i]->visited = 1;
                queue[rear++] = i;
            }
        }
    }
    printf("\n");
}

int main() {
    graph* G = creategraph();
    int n, e, u, v, start;

    printf("Enter number of vertices: ");
    scanf("%d", &n);
    if (n <= 0 || n > MAX) {
        printf("Invalid number of vertices\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
        insertnode(G, i);

    printf("Enter number of edges: ");
    scanf("%d", &e);
    if (e < 0 || e > n * (n - 1) / 2) {
        printf("Invalid number of edges\n");
        return 1;
    }

    printf("Enter edges (u v), using vertices 0 to %d:\n", n - 1);
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        insertedge(G, u, v);
    }

    displaygraph(G);
    printf("Enter starting vertex for BFS: ");
    scanf("%d", &start);
    BFS(G, start);

    for (int i = 0; i < G->count; i++)
        free(G->nodes[i]);
    free(G);

    return 0;
}