#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int *arr;
    int front;
    int rear;
    int size;
}circularqueue;

circularqueue* createqueue(int given_size){
    circularqueue* Q = (circularqueue*)malloc(sizeof(circularqueue));

    if(Q == NULL){printf("createqueue failed\n");exit(1);}

    Q->arr = (int*)malloc(given_size * sizeof(int));

    if(Q->arr == NULL){printf("array allocation failed\n");exit(1);}

    Q->front = -1;
    Q->rear = -1;
    Q->size = given_size;

    return Q;
}

int isEmpty(circularqueue* Q){
    return Q->front == -1;
}

int isFull(circularqueue* Q){
    return (Q->rear + 1) % Q->size == Q->front;
}

void enqueue(circularqueue* Q, int value){
    if(isFull(Q)){
        printf("Queue is full\n");
        return;
    }

    if(isEmpty(Q)){
        Q->front = 0;
        Q->rear = 0;
    }else{
        Q->rear = (Q->rear + 1) % Q->size;
    }

    Q->arr[Q->rear] = value;
    printf("%d inserted into queue\n", value);
}

void dequeue(circularqueue* Q){
    if(isEmpty(Q)){
        printf("Queue is empty\n");
        return;
    }

    printf("Deleted element : %d\n", Q->arr[Q->front]);

    if(Q->front == Q->rear){
        Q->front = -1;
        Q->rear = -1;
    }else{
        Q->front = (Q->front + 1) % Q->size;
    }
}

void display(circularqueue* Q){
    if(isEmpty(Q)){
        printf("Queue is empty\n");
        return;
    }

    int curr = Q->front;

    printf("Queue : ");

    while(1){
        printf("%d ", Q->arr[curr]);

        if(curr == Q->rear)
            break;

        curr = (curr + 1) % Q->size;
    }

    printf("\n");
}

int main(){

    int size;
    int opcode = 0;
    int operand = 0;

    printf("Enter queue size : ");
    scanf("%d", &size);

    circularqueue* Q = createqueue(size);

    while(1){

        printf("\n");
        display(Q);

        printf("\nSelect action : \
        \n1 enqueue\
        \n2 dequeue\
        \n3 display\
        \n4 exit\
        \n\t\t:");

        scanf("%d",&opcode);

        switch(opcode)
        {
            case 1:
                printf("Enter element : ");
                scanf("%d",&operand);

                enqueue(Q, operand);

                break;

            case 2:
                dequeue(Q);

                break;

            case 3:
                display(Q);

                break;

            case 4:
                printf("\nprogram exiting\n");

                free(Q->arr);
                free(Q);

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