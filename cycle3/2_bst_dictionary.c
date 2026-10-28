#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char word[50];
    char meaning[200];
    struct node *left, *right;
} node;

typedef struct {
    node *root;
} tree;

node* createnode(char word[], char meaning[]) {
    node *n = (node*)malloc(sizeof(node));
    if (n == NULL) {
        printf("error at node allocation");
        exit(0);
    }
    strcpy(n->word, word);
    strcpy(n->meaning, meaning);
    n->left = n->right = NULL;
    return n;
}

void displaynode(node *n) {
    if (n == NULL) {
        printf("node is NULL\n");
        return;
    }
    printf("%s : %s", n->word, n->meaning);
}

tree* createtree() {
    tree *t = (tree*)malloc(sizeof(tree));
    if (t == NULL) {
        printf("error at tree allocation");
        exit(0);
    }
    t->root = NULL;
    return t;
}

void inorder(node *m) {
    if (m != NULL) {
        inorder(m->left);
        displaynode(m);
        printf("\n");
        inorder(m->right);
    }
}

node* Iinsertnode(node *m, node *n) {
    if (m == NULL)
        m = n;
    else if (strcmp(m->word, n->word) > 0)
        m->left = Iinsertnode(m->left, n);
    else if (strcmp(m->word, n->word) < 0)
        m->right = Iinsertnode(m->right, n);
    else {
        printf("Word already exists.\n");
        strcpy(m->meaning, n->meaning);
        free(n);
    }
    return m;
}

void insertnode(tree *T, char word[], char meaning[]) {
    node *n = createnode(word, meaning);
    T->root = Iinsertnode(T->root, n);
}

node* searchnode(node *m, char word[]) {
    if (m == NULL)
        return NULL;
    if (strcmp(m->word, word) == 0)
        return m;
    else if (strcmp(m->word, word) > 0)
        return searchnode(m->left, word);
    else
        return searchnode(m->right, word);
}

void searchword(tree *T, char word[]) {
    node *result = searchnode(T->root, word);
    if (result == NULL)
        printf("Word not found.\n");
    else
        printf("Meaning: %s\n", result->meaning);
}

void display(tree *T) {
    if (T->root == NULL)
        printf("Dictionary is empty.\n");
    else {
        printf("Dictionary (alphabetical order):\n");
        inorder(T->root);
    }
}

int main() {
    tree *T = createtree();
    int opcode;
    char word[50], meaning[200];

    while (1) {
        display(T);
        printf("\n\nDictionary using Binary Search Tree\n");
        printf("-----------------------------------\n");
        printf("1. Insert word\n");
        printf("2. Search word\n");
        printf("3. Exit\n");
        printf("\nSelect action : ");
        scanf("%d", &opcode);

        switch (opcode) {
            case 1:
                printf("\nEnter word: ");
                scanf("%49s", word);
                printf("Enter meaning: ");
                scanf(" %199[^\n]", meaning);
                insertnode(T, word, meaning);
                break;

            case 2:
                printf("\nEnter word to search: ");
                scanf("%49s", word);
                searchword(T, word);
                break;

            case 3:
                printf("\nProgram exiting\n");
                exit(0);

            default:
                printf("\nInvalid option");
                break;
        }
    }
    return 0;
}