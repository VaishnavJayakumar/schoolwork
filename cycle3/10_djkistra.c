#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 100
#define INF INT_MAX

typedef struct node {
    int data, weight;
    struct node* next;
} node;

typedef struct graph {
    int vertices;
    node* adj[MAX_NODES];
} graph;

node* createnode(int value, int weight) {
    node* n = (node*)malloc(sizeof(node));
    if (n == NULL) {
        printf("error at node allocation\n");
        exit(1);
    }
    n->data = value;
    n->weight = weight;
    n->next = NULL;
    return n;
}

graph* creategraph(int vertices) {
    graph* G = (graph*)malloc(sizeof(graph));
    if (G == NULL) {
        printf("error at graph allocation\n");
        exit(1);
    }
    G->vertices = vertices;
    for (int i = 0; i < vertices; i++)
        G->adj[i] = NULL;
    return G;
}

void insertnode(graph* G, int source, int destination, int weight) {
    node* n = createnode(destination, weight);
    n->next = G->adj[source];
    G->adj[source] = n;
}

void insertedge(graph* G, int source, int destination, int weight) {
    insertnode(G, source, destination, weight);
    insertnode(G, destination, source, weight);
}

int findmin(int distance[], int visited[], int vertices) {
    int min = INF, minindex = -1;
    for (int i = 0; i < vertices; i++) {
        if (!visited[i] && distance[i] < min) {
            min = distance[i];
            minindex = i;
        }
    }
    return minindex;
}

void dijkstra(graph* G, int source) {
    int distance[MAX_NODES], visited[MAX_NODES], parent[MAX_NODES];

    for (int i = 0; i < G->vertices; i++) {
        distance[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }
    distance[source] = 0;

    for (int i = 0; i < G->vertices; i++) {
        int u = findmin(distance, visited, G->vertices);
        if (u == -1)
            break;

        visited[u] = 1;
        node* temp = G->adj[u];

        while (temp != NULL) {
            int v = temp->data, weight = temp->weight;
            if (!visited[v] && distance[u] != INF && weight >= 0 &&
                distance[u] <= INT_MAX - weight &&
                distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }

    printf("\nShortest paths from node %d:\n", source);
    for (int i = 0; i < G->vertices; i++) {
        if (distance[i] == INF) {
            printf("%d -> %d : Unreachable\n", source, i);
        } else {
            printf("%d -> %d : Distance = %d, Path = ",
                   source, i, distance[i]);

            int path[MAX_NODES], count = 0, current = i;
            while (current != -1) {
                path[count++] = current;
                current = parent[current];
            }

            for (int j = count - 1; j >= 0; j--) {
                printf("%d", path[j]);
                if (j > 0)
                    printf(" -> ");
            }
            printf("\n");
        }
    }
}

void displaygraph(graph* G) {
    printf("\nAdjacency List:\n");
    for (int i = 0; i < G->vertices; i++) {
        printf("%d : ", i);
        node* temp = G->adj[i];

        while (temp != NULL) {
            printf("(%d, weight=%d) -> ", temp->data, temp->weight);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void freegraph(graph* G) {
    for (int i = 0; i < G->vertices; i++) {
        node* temp = G->adj[i];
        while (temp != NULL) {
            node* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(G);
}

int main() {
    int opcode, vertices, edges, source, destination, weight;

    printf("Enter number of vertices (max %d): ", MAX_NODES);
    scanf("%d", &vertices);
    if (vertices <= 0 || vertices > MAX_NODES) {
        printf("Invalid number of vertices\n");
        return 1;
    }

    graph* G = creategraph(vertices);
    printf("Enter number of edges: ");
    scanf("%d", &edges);

    if (edges < 0) {
        printf("Invalid number of edges\n");
        freegraph(G);
        return 1;
    }

    for (int i = 0; i < edges; i++) {
        printf("Enter source, destination and weight: ");
        scanf("%d %d %d", &source, &destination, &weight);

        if (source < 0 || source >= vertices ||
            destination < 0 || destination >= vertices || weight < 0) {
            printf("Invalid edge or weight. Try again.\n");
            i--;
            continue;
        }
        insertedge(G, source, destination, weight);
    }

    while (1) {
        printf("\n\nSelect action:");
        printf("\n1. Display graph\n2. Dijkstra shortest path");
        printf("\n3. Exit\n\t: ");

        if (scanf("%d", &opcode) != 1)
            break;

        switch (opcode) {
            case 1:
                displaygraph(G);
                break;
            case 2:
                printf("Enter source vertex: ");
                scanf("%d", &source);
                if (source < 0 || source >= G->vertices) {
                    printf("Invalid source vertex\n");
                    break;
                }
                dijkstra(G, source);
                break;
            case 3:
                printf("Program exiting\n");
                freegraph(G);
                return 0;
            default:
                printf("Invalid option\n");
        }
    }

    freegraph(G);
    return 0;
}