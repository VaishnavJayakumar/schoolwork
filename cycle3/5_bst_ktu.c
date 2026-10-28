#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *left, *right;
} node;

typedef struct {
    node *root;
} tree;

node* createnode(int value) {
    node *n = (node*)malloc(sizeof(node));
    if (n == NULL) {
        printf("Error at node allocation\n");
        exit(1);
    }
    n->data = value;
    n->left = n->right = NULL;
    return n;
}

tree* createtree() {
    tree *T = (tree*)malloc(sizeof(tree));
    if (T == NULL) {
        printf("Error at tree allocation\n");
        exit(1);
    }
    T->root = NULL;
    return T;
}

void insertnode(tree *T, int value, int capacity) {
    node *n = createnode(value);
    if (T->root == NULL) {
        T->root = n;
        return;
    }

    node **queue = (node**)malloc(capacity * sizeof(node*));
    if (queue == NULL) {
        printf("Error at queue allocation\n");
        exit(1);
    }

    int front = 0, rear = 0;
    queue[rear++] = T->root;

    while (front < rear) {
        node *current = queue[front++];
        if (current->left == NULL) {
            current->left = n;
            break;
        } else queue[rear++] = current->left;

        if (current->right == NULL) {
            current->right = n;
            break;
        } else queue[rear++] = current->right;
    }
    free(queue);

    node *current = n, *parent = NULL;
    while (current != T->root) {
        queue = (node**)malloc(capacity * sizeof(node*));
        if (queue == NULL) {
            printf("Error at queue allocation\n");
            exit(1);
        }
        front = rear = 0;
        queue[rear++] = T->root;

        while (front < rear) {
            node *temp = queue[front++];
            if (temp->left == current || temp->right == current) {
                parent = temp;
                break;
            }
            if (temp->left != NULL) queue[rear++] = temp->left;
            if (temp->right != NULL) queue[rear++] = temp->right;
        }
        free(queue);

        if (parent == NULL || current->data <= parent->data)
            break;

        int temp = current->data;
        current->data = parent->data;
        parent->data = temp;
        current = parent;
        parent = NULL;
    }
}

void heapify(node *current) {
    if (current == NULL) return;
    node *largest = current;
    if (current->left != NULL && current->left->data > largest->data)
        largest = current->left;
    if (current->right != NULL && current->right->data > largest->data)
        largest = current->right;
    if (largest != current) {
        int temp = current->data;
        current->data = largest->data;
        largest->data = temp;
        heapify(largest);
    }
}

int extractmax(tree *T, int capacity) {
    int maximum = T->root->data;
    if (T->root->left == NULL && T->root->right == NULL) {
        free(T->root);
        T->root = NULL;
        return maximum;
    }

    node **queue = (node**)malloc(capacity * sizeof(node*));
    node **parents = (node**)malloc(capacity * sizeof(node*));
    if (queue == NULL || parents == NULL) {
        printf("Error at queue allocation\n");
        exit(1);
    }

    int front = 0, rear = 0;
    node *last = NULL, *parent = NULL;
    queue[rear++] = T->root;

    while (front < rear) {
        node *current = queue[front++];
        last = current;
        if (current->left != NULL) {
            parents[rear] = current;
            queue[rear++] = current->left;
        }
        if (current->right != NULL) {
            parents[rear] = current;
            queue[rear++] = current->right;
        }
    }

    if (last != T->root) {
        parent = parents[rear - 1];
        T->root->data = last->data;
        if (parent->right == last) parent->right = NULL;
        else parent->left = NULL;
        free(last);
    }
    free(queue);
    free(parents);
    heapify(T->root);
    return maximum;
}

void freetree(node *current) {
    if (current == NULL) return;
    freetree(current->left);
    freetree(current->right);
    free(current);
}

int main() {
    tree *T = createtree();
    int n, k, value;
    long long points = 0;

    printf("Enter number of events and maximum events allowed: ");
    if (scanf("%d %d", &n, &k) != 2 || n < 0 || k < 0) {
        printf("Invalid input\n");
        free(T);
        return 1;
    }
    if (n == 0 || k == 0) {
        printf("Maximum activity points = 0\n");
        free(T);
        return 0;
    }

    printf("Enter activity points of each event:\n");
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &value) != 1) {
            printf("Invalid input\n");
            freetree(T->root);
            free(T);
            return 1;
        }
        insertnode(T, value, n);
    }

    int limit = (k < n) ? k : n;
    for (int i = 0; i < limit && T->root != NULL; i++) {
        if (T->root->data <= 0) break;
        points += extractmax(T, n);
    }

    printf("Maximum activity points = %lld\n", points);
    freetree(T->root);
    free(T);
    return 0;
}