#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* link;
}node;

typedef struct{node* head;}linkedlist;

node* createnode(int given_value){
    node* n = malloc(sizeof(node));
    if(n == NULL){printf("createnode failed");exit(1);}
    n->data = given_value;
    n->link = NULL;
    return n;
};

linkedlist* createlist() {
    linkedlist* L = malloc(sizeof(linkedlist));
    if(L == NULL){printf("createlist failed\n");exit(1);}
    L->head = NULL;
    return L;
}

void display(linkedlist* L){
    if (L->head == NULL) {
        printf("\nEmpty linked list\n");
        return;
    }
    node* curr = L->head;
    printf("\nll stack: ");
    while (curr != NULL) {
        printf(" %d -->", curr->data);
        curr = curr->link;
    }
    printf("|<\n");
}

void appendnode(linkedlist* L, int given_value){
    node* new_node = createnode(given_value);
    if (L->head == NULL) {
        L->head = new_node;
        return;
    }
    node* curr = L->head;
    while (curr->link != NULL) {
        curr = curr->link;
    }
    curr->link = new_node;
}

void popnode(linkedlist* L){
    if (L->head == NULL) {
        printf("No elements to pop");
        return;
    }
    if (L->head->link == NULL) {
        printf("Popped value: %d", L->head->data);
        free(L->head);
        L->head = NULL;
        return;
    }
    node* curr = L->head;
    while (curr->link->link != NULL) {
        curr = curr->link;
    }
    printf("Popped value: %d", curr->link->data);
    free(curr->link);
    curr->link = NULL;
}

int main(){
    linkedlist* A = createlist();
    int opcode = 0;
    int operand = 0;
    while(1){
        display(A);
        printf("\nSelect action : \
            \n1 push node\
            \n2 pop node \
            \n3 exit\
            \n\t\t:");
        scanf("%d",&opcode);

        switch (opcode)
        {
        case 1:
            printf("\nnewnode value:");
            scanf("%d",&operand);
            appendnode(A,operand);
            break;
        
        case 2:
            popnode(A);
            break;

        case 3:
            printf("\nprogram exiting\n");
            exit(0);
            break;

        default:
            printf("\nInvalid option");
            break;
    }}
    printf("\n");
    return 0;
}