#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct{
    int arr[MAX];
    int front;
    int rear;
}queue;

queue* createqueue(){
    queue* Q = (queue*)malloc(sizeof(queue));

    if(Q == NULL){printf("createqueue failed\n");exit(1);}

    Q->front = -1;
    Q->rear = -1;
    return Q;
}

void enqueue(queue* Q, int value){
    if(Q->rear == MAX - 1){
        printf("Queue overflow\n");
        return;
    }

    if(Q->front == -1){
        Q->front = 0;
    }

    Q->rear++;
    Q->arr[Q->rear] = value;
}

void dequeue(queue* Q){
    if(Q->front == -1 || Q->front > Q->rear){
        printf("Queue underflow\n");
        return;
    }

    printf("Dequeued %d\n", Q->arr[Q->front]);
    Q->front++;

    if(Q->front > Q->rear){
        Q->front = -1;
        Q->rear = -1;
    }
}

void display(queue* Q){
    if(Q->front == -1){
        printf("Queue is empty\n");
        return;
    }

    printf("Queue : ");

    for(int i = Q->front; i <= Q->rear; i++){
        printf("%d ", Q->arr[i]);
    }

    printf("\n");
}

int main(){

    queue* Q = createqueue();

    int opcode = 0;
    int operand = 0;

    while(1){

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
            printf("\nEnter value: ");
            scanf("%d",&operand);

            enqueue(Q,operand);
            break;

        case 2:
            dequeue(Q);
            break;

        case 3:
            display(Q);
            break;

        case 4:
            printf("\nprogram exiting\n");
            free(Q);
            exit(0);
            break;

        default:
            printf("\nInvalid option\n");
            break;
        }
    }

    return 0;
}