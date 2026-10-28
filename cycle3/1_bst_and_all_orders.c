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
        printf("Error at node allocation");
        exit(0);
    }
    n->data = value;
    n->left = n->right = NULL;
    return n;
}

void displaynode(node *n) {
    if (n == NULL) printf("Node is NULL\n");
    else printf("%d", n->data);
}

tree* createtree() {
    tree *t = (tree*)malloc(sizeof(tree));
    if (t == NULL) {
        printf("Error at tree allocation");
        exit(0);
    }
    t->root = NULL;
    return t;
}

void preorder(node *m) {
    if (m != NULL) {
        displaynode(m);
        printf(",");
        preorder(m->left);
        preorder(m->right);
    }
}

void inorder(node *m) {
    if (m != NULL) {
        inorder(m->left);
        displaynode(m);
        printf(",");
        inorder(m->right);
    }
}

void postorder(node *m) {
    if (m != NULL) {
        postorder(m->left);
        postorder(m->right);
        displaynode(m);
        printf(",");
    }
}

void traverse(tree *T, int mode) {
    node *m = T->root;
    if (m == NULL) {
        printf("Tree is empty\n");
        return;
    }
    if (mode == -1) {
        printf("Preorder: ");
        preorder(m);
    } else if (mode == 0) {
        printf("Inorder: ");
        inorder(m);
    } else if (mode == 1) {
        printf("Postorder: ");
        postorder(m);
    }
    printf("\n");
}

node* Iinsertnode(node *m, node *n) {
    if (m == NULL) m = n;
    else if (m->data > n->data) m->left = Iinsertnode(m->left, n);
    else if (m->data < n->data) m->right = Iinsertnode(m->right, n);
    return m;
}

void insertnode(tree *T, int value) {
    T->root = Iinsertnode(T->root, createnode(value));
}

int main() {
    tree *T = createtree();
    int opcode, operand;

    while (1) {
        traverse(T, -1);
        traverse(T, 0);
        traverse(T, 1);
        printf("\nSelect action:\n1. Insert node\n2. Exit\n\t:");
        scanf("%d", &opcode);

        switch (opcode) {
            case 1:
                printf("New node value: ");
                scanf("%d", &operand);
                insertnode(T, operand);
                break;
            case 2:
                printf("Program exiting\n");
                exit(0);
            default:
                printf("Invalid option\n");
        }
    }
    return 0;
}