#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node* left;
    struct node* right;
}node;


typedef struct{
    node* root;
}tree;


node* createnode(int value){
    node* n = (node*)malloc(sizeof(node));
    
    if(n == NULL){
        printf("error at node allocation");
        exit(0);
    }

    n->data = value;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void debugnode(node* n){
    if(n == NULL){
        printf("node is NULL \n");
        return;
    }
    printf("%p %d %p %p \n",n,n->data,n->left,n->right);
}

void displaynode(node* n){
    if(n == NULL){
        printf("node is NULL \n");
        return;
    }
    printf("%d",n->data);
}

tree* createtree(){
    tree* t = (tree*)malloc(sizeof(tree));
    
    if(t == NULL){
        printf("error at tree allocation");
        exit(0);
    }

    t->root = NULL;
    return t;
}

void preorder(node* m){
    if(m != NULL){
        displaynode(m);
        printf(",");
        preorder(m->left);
        preorder(m->right);
    }
}

void inorder(node* m){
    if(m != NULL){
        inorder(m->left);
        displaynode(m);
        printf(",");
        inorder(m->right);
    }
}

void postorder(node* m){
    if(m != NULL){
        postorder(m->left);
        postorder(m->right);
        displaynode(m);
        printf(",");
    }
}

void traverse(tree* T,int mode){
    node* m = T->root;
    if(m == NULL){
        printf("Tree is empty");
        return;
    }
    else if(mode == -1){
        printf("preorder : ");
        preorder(m);
    }
    else if(mode == 0){
        printf("inorder : ");
        inorder(m);
    }
    else if(mode == 1){
        printf("postorder : ");
        postorder(m);
    }
    printf("\n");
}


node* Iinsertnode(node* m,node* n){
    if(m == NULL){
        m = n;
    }
    else if(m->data > n->data){
        m->left = Iinsertnode(m->left,n);
    }
    else if(m->data < n->data){
        m->right = Iinsertnode(m->right,n);
    }
    return m;
}

void insertnode(tree* T, int value){
    node* n = createnode(value);
    T->root = Iinsertnode(T->root,n);
}


int main(){
    tree* T = createtree();
    int opcode = 0;
    int operand = 0;
    while (1) {
        traverse(T,-1);
        traverse(T,0);
        traverse(T,1);
        printf("\n\nSelect action : \
        \n1 insert node\
        \n2 exit\
        \n\t\t:");
        scanf("%d", &opcode);
        switch (opcode) {
            case 1:
                printf("\nnewnode value:");
                scanf("%d", &operand);
                insertnode(T, operand);
                break;

            case 2:
                printf("\nprogram exiting\n");
                exit(0);
                break;

            default:
                printf("\nInvalid option");
                break;
        }
    }
    
    printf("\n");
    return 0;
}