#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} node;

typedef struct graph {
    int V;
    node** adj;
} graph;

node* createnode(int value) {
    node* n = (node*)malloc(sizeof(node));
    if (n == NULL) {
        printf("Error at node allocation\n");
        exit(1);
    }
    n->data = value;
    n->next = NULL;
    return n;
}

graph* creategraph(int V) {
    graph* G = (graph*)malloc(sizeof(graph));
    if (G == NULL) {
        printf("Error at graph allocation\n");
        exit(1);
    }
    G->V = V;
    G->adj = (node**)calloc(V, sizeof(node*));
    if (G->adj == NULL) {
        printf("Error at adjacency list allocation\n");
        exit(1);
    }
    return G;
}

void addedge(graph* G, int src, int dest) {
    node* n = createnode(dest);
    n->next = G->adj[src];
    G->adj[src] = n;

    n = createnode(src);
    n->next = G->adj[dest];
    G->adj[dest] = n;
}

void DFS(graph* G, int v, int visited[]) {
    visited[v] = 1;
    node* temp = G->adj[v];

    while (temp != NULL) {
        if (visited[temp->data] == 0)
            DFS(G, temp->data, visited);
        temp = temp->next;
    }
}

int isconnected(graph* G) {
    if (G->V == 0)
        return 0;

    int* visited = (int*)calloc(G->V, sizeof(int));
    if (visited == NULL) {
        printf("Error at visited allocation\n");
        exit(1);
    }

    DFS(G, 0, visited);

    for (int i = 0; i < G->V; i++) {
        if (visited[i] == 0) {
            free(visited);
            return 0;
        }
    }

    free(visited);
    return 1;
}

void displaygraph(graph* G) {
    for (int i = 0; i < G->V; i++) {
        printf("%d : ", i);
        node* temp = G->adj[i];

        while (temp != NULL) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void freegraph(graph* G) {
    for (int i = 0; i < G->V; i++) {
        node* temp = G->adj[i];

        while (temp != NULL) {
            node* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(G->adj);
    free(G);
}

int main() {
    int V, E, src, dest;
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    if (V <= 0) {
        printf("Number of vertices must be positive\n");
        return 1;
    }

    graph* G = creategraph(V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    if (E < 0) {
        printf("Number of edges cannot be negative\n");
        freegraph(G);
        return 1;
    }

    printf("Enter edges (source destination):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d", &src, &dest);

        if (src < 0 || src >= V || dest < 0 || dest >= V) {
            printf("Invalid vertex number\n");
            freegraph(G);
            return 1;
        }
        addedge(G, src, dest);
    }

    printf("\nAdjacency List:\n");
    displaygraph(G);

    if (isconnected(G))
        printf("\nGraph is connected\n");
    else
        printf("\nGraph is not connected\n");

    freegraph(G);
    return 0;
}