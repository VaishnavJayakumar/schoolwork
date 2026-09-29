#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct{
    int arr[SIZE];
    int front;
    int rear;
}deque;

deque* createdeque(){
    deque* D = (deque*)malloc(sizeof(deque));

    if(D == NULL){printf("createdeque failed\n");exit(1);}

    D->front = -1;
    D->rear = -1;

    return D;
}

int isEmpty(deque* D){
    return D->front == -1;
}

int isFull(deque* D){
    return (D->front == 0 && D->rear == SIZE-1) ||
           (D->front == D->rear + 1);
}

void insertFront(deque* D, int value){
    if(isFull(D)){
        printf("Deque is full\n");
        return;
    }

    if(isEmpty(D)){
        D->front = 0;
        D->rear = 0;
    }
    else if(D->front == 0){
        D->front = SIZE - 1;
    }
    else{
        D->front--;
    }

    D->arr[D->front] = value;
}

void insertRear(deque* D, int value){
    if(isFull(D)){
        printf("Deque is full\n");
        return;
    }

    if(isEmpty(D)){
        D->front = 0;
        D->rear = 0;
    }
    else if(D->rear == SIZE - 1){
        D->rear = 0;
    }
    else{
        D->rear++;
    }

    D->arr[D->rear] = value;
}

void deleteFront(deque* D){
    if(isEmpty(D)){
        printf("Deque is empty\n");
        return;
    }

    printf("Deleted %d\n", D->arr[D->front]);

    if(D->front == D->rear){
        D->front = -1;
        D->rear = -1;
    }
    else if(D->front == SIZE - 1){
        D->front = 0;
    }
    else{
        D->front++;
    }
}

void deleteRear(deque* D){
    if(isEmpty(D)){
        printf("Deque is empty\n");
        return;
    }

    printf("Deleted %d\n", D->arr[D->rear]);

    if(D->front == D->rear){
        D->front = -1;
        D->rear = -1;
    }
    else if(D->rear == 0){
        D->rear = SIZE - 1;
    }
    else{
        D->rear--;
    }
}

void display(deque* D){
    if(isEmpty(D)){
        printf("Deque is empty\n");
        return;
    }

    int i = D->front;

    printf("Deque : ");

    while(1){
        printf("%d ", D->arr[i]);

        if(i == D->rear)
            break;

        i = (i + 1) % SIZE;
    }

    printf("\n");
}

int main(){

    deque* D = createdeque();

    int opcode = 0;
    int operand = 0;

    while(1){

        display(D);

        printf("\nSelect action : \
        \n1 insert at front\
        \n2 insert at rear\
        \n3 delete from front\
        \n4 delete from rear\
        \n5 exit\
        \n\t\t:");

        scanf("%d",&opcode);

        switch(opcode)
        {
        case 1:
            printf("Enter value: ");
            scanf("%d",&operand);

            insertFront(D, operand);

            break;

        case 2:
            printf("Enter value: ");
            scanf("%d",&operand);

            insertRear(D, operand);

            break;

        case 3:
            deleteFront(D);

            break;

        case 4:
            deleteRear(D);

            break;

        case 5:
            printf("\nprogram exiting\n");

            free(D);

            exit(0);

            break;

        default:
            printf("\nInvalid option\n");

            break;
        }
    }

    return 0;
}