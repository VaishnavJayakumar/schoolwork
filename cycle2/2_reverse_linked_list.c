#include <stdio.h>
#include <stdlib.h>


typedef struct node{
    int data;
    struct node* link;
}node;

node* createnode(int given_value){
    node* n = (node*)malloc(sizeof(node));
    if(n == NULL){printf("createnode failed");exit(1);}
    n->data = given_value;
    n->link = NULL;
    return n;
};

typedef struct{ //linked list
    node* head;
}linkedlist;

linkedlist* createlist() {
    linkedlist* L = (linkedlist*)malloc(sizeof(linkedlist));
    if(L == NULL){printf("createlist failed\n");exit(1);}
    L->head = NULL;
    return L;
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

void reverse(linkedlist* L){
    node* prev = NULL;
    node* curr = L->head;
    node* next = NULL;
    while (curr != NULL) {
        next = curr->link; // Store next node
        curr->link = prev; // Reverse the link
        prev = curr;       // Move prev to current
        curr = next;      // Move to next node
    }
    L->head = prev; // Update head to new first node
}

void display(linkedlist* L){

    if (L->head == NULL) {
        printf("\nEmpty linked list\n");
        return;
    }
    node* curr = L->head;
    printf("\nll state: ");
    while (curr != NULL) { 
        printf(" %d -->", curr->data);
        curr = curr->link;
    }
    printf("|<\n");
}

int main(){
    linkedlist* A = createlist();
    int opcode = 0;
    int operand = 0;
    int operand2 = 0;
    while(1){
    display(A);
    printf("\nSelect action : \
        \n1 insert node at end\
        \n2 delete node at end \
        \n3 reverse linked list\
        \n4 exit\
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
        printf("\nreversing linked list");
        reverse(A);
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
