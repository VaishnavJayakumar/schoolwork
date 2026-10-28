#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct node {
    int data, visited;
} node;

typedef struct {
    int vertices;
    int adj[MAX][MAX];
    node nodes[MAX];
} graph;

graph* creategraph(int n) {
    graph *G = (graph*)malloc(sizeof(graph));
    if (G == NULL) {
        printf("Error at graph allocation\n");
        exit(1);
    }
    G->vertices = n;
    for (int i = 0; i < n; i++) {
        G->nodes[i].data = i;
        G->nodes[i].visited = 0;
        for (int j = 0; j < n; j++)
            G->adj[i][j] = 0;
    }
    return G;
}

void addedge(graph *G, int u, int v) {
    if (u < 0 || u >= G->vertices || v < 0 || v >= G->vertices) {
        printf("Invalid vertex\n");
        return;
    }
    G->adj[u][v] = G->adj[v][u] = 1;
}

void displaymatrix(graph *G) {
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < G->vertices; i++) {
        for (int j = 0; j < G->vertices; j++)
            printf("%d ", G->adj[i][j]);
        printf("\n");
    }
}

void DFS(graph *G, int v) {
    G->nodes[v].visited = 1;
    printf("%d ", G->nodes[v].data);
    for (int i = 0; i < G->vertices; i++)
        if (G->adj[v][i] == 1 && G->nodes[i].visited == 0)
            DFS(G, i);
}

void traverse(graph *G, int start) {
    if (G->vertices == 0) {
        printf("Graph is empty\n");
        return;
    }
    if (start < 0 || start >= G->vertices) {
        printf("Invalid starting vertex\n");
        return;
    }
    for (int i = 0; i < G->vertices; i++)
        G->nodes[i].visited = 0;
    printf("DFS Traversal: ");
    DFS(G, start);
    for (int i = 0; i < G->vertices; i++)
        if (G->nodes[i].visited == 0)
            DFS(G, i);
    printf("\n");
}

int main() {
    graph *G;
    int n, edges, u, v, opcode;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    if (n < 1 || n > MAX) {
        printf("Invalid number of vertices\n");
        return 1;
    }
    G = creategraph(n);
    printf("Enter number of edges: ");
    scanf("%d", &edges);
    if (edges < 0 || edges > n * (n - 1) / 2) {
        printf("Invalid number of edges\n");
        free(G);
        return 1;
    }
    for (int i = 0; i < edges; i++) {
        printf("Enter edge (u v): ");
        scanf("%d %d", &u, &v);
        addedge(G, u, v);
    }

    while (1) {
        printf("\n\nSelect action:\n1. Display adjacency matrix\n2. Perform DFS\n3. Exit\nEnter option: ");
        scanf("%d", &opcode);
        switch (opcode) {
            case 1:
                displaymatrix(G);
                break;
            case 2:
                printf("Enter starting vertex: ");
                scanf("%d", &u);
                traverse(G, u);
                break;
            case 3:
                printf("Program exiting\n");
                free(G);
                return 0;
            default:
                printf("Invalid option\n");
                break;
        }
    }
}