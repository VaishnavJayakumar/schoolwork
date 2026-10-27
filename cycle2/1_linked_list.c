#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* link;
}node;

typedef struct{node* head;}linkedlist;

//#/
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
    printf("\nll state: ");
    while (curr != NULL) { 
        printf(" %d -->", curr->data);
        curr = curr->link;
    }
    printf("|<\n");
}
//#/

void prependnode(linkedlist* L, int given_value){
    node* new_node = createnode(given_value);
    new_node->link = L->head;
    L->head = new_node;
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

void insertnode(linkedlist* L, int given_value,int pos){
    node* new_node = createnode(given_value);
    if (pos == 0) {
        new_node->link = L->head;
        L->head = new_node;
        return;
    }
    node* curr = L->head;
    for (int i = 0; i < pos - 1 && curr != NULL; i++) {
        curr = curr->link;
    }
    if (curr == NULL) {
        printf("Position out of bounds\n");
        free(new_node);
        return;
    }
    new_node->link = curr->link;
    curr->link = new_node; 
    printf("Inserted %d at position %d\n",given_value,pos);  
}

void deletenode(linkedlist* L,int pos){
    if (L->head == NULL) {
        printf("No elements to delete");
        return;
    }
    if (pos == 0) {
        node* temp = L->head;
        L->head = L->head->link;
        free(temp);
        printf("element index 0 deleted");
        return;
    }
    node* prev = L->head;
    node* curr = prev->link;
    for (int i = 0; i < pos - 1 && curr != NULL; i++) {
        prev = prev->link;
        curr = curr->link;
    }
    if(curr == NULL){
        printf("Invalid position %d, node does not exist",pos);
        return;
        }
    prev->link = curr->link;
    free(curr);
    printf("element index %d deleted",pos);
}

void deletevalue(linkedlist* L, int val){
    int flag = 0;
    int pos = 0;
    if (L->head == NULL){
        printf("\nEmpty linked list\n");
        return;
    }
    node dummy;
    dummy.link = L->head;
    node* prev = &dummy;
    node* curr = prev->link;
    while (curr != NULL){
        if (curr->data == val){
            node* toDelete = curr;
            prev->link = curr->link;
            curr = prev->link;
            free(toDelete);
            printf("\nelement index %d deleted", pos);
            flag = 1;
        } else {
            prev = curr;
            curr = curr->link;
        }
        pos++;
    }
    L->head = dummy.link;
    if (!flag){
        printf("No elements are deleted");
    }
}

int main() {
    linkedlist *A = createlist();
    int opcode = 0;
    int operand = 0;
    int operand2 = 0;
    while (1) {
        display(A);
        printf("\nSelect action : \
        \n1 insert node at beginning\
        \n2 insert node at a position\
        \n3 insert node at end\
        \n4 delete node at a position\
        \n5 delete node by a particularvalue\
        \n6 exit\
        \n\t\t:");
        scanf("%d", &opcode);
        switch (opcode) {
            case 1:
                printf("\nnewnode value:");
                scanf("%d", &operand);
                prependnode(A, operand);
                break;

            case 2:
                printf("\nnewnode position:");
                scanf("%d", &operand2);
                printf("\nnewnode value:");
                scanf("%d", &operand);
                insertnode(A, operand, operand2);
                break;

            case 3:
                printf("\nnewnode value:");
                scanf("%d", &operand);
                appendnode(A, operand);
                break;

            case 4:
                printf("\ndeleting node position:");
                scanf("%d", &operand);
                deletenode(A, operand);
                break;

            case 5:
                printf("\ndeleting node of value:");
                scanf("%d", &operand);
                deletevalue(A, operand);
                break;

            case 6:
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
