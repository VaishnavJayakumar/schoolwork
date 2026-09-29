#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int row;
    int col;
    int value;
}entry;

void inputmatrix(entry A[], int *n){
    int i;

    printf("\nEnter number of non-zero elements: ");
    scanf("%d", n);

    for(i=0;i<*n;i++){
        printf("\nEnter row: ");
        scanf("%d",&A[i].row);

        printf("\nEnter column: ");
        scanf("%d",&A[i].col);

        printf("\nEnter value: ");
        scanf("%d",&A[i].value);
    }
}

void display(entry A[], int n){
    int i;

    if(n==0){
        printf("Empty matrix\n");
        return;
    }

    printf("\nSparse matrix:\n");
    printf("Row\tColumn\tValue\n");

    for(i=0;i<n;i++){
        printf("%d\t%d\t%d\n",A[i].row,A[i].col,A[i].value);
    }
}

void sortmatrix(entry A[], int n){
    int i,j;
    entry temp;

    for(i=0;i<n-1;i++){
        for(j=0;j<n-i-1;j++){
            if(A[j].row > A[j+1].row ||
              (A[j].row == A[j+1].row && A[j].col > A[j+1].col)){

                temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
            }
        }
    }
}

void addmatrix(entry A[],int n1,entry B[],int n2,entry C[],int *n3){
    int i=0,j=0,k=0;

    while(i<n1 && j<n2){

        if(A[i].row == B[j].row && A[i].col == B[j].col){

            if(A[i].value + B[j].value != 0){
                C[k].row = A[i].row;
                C[k].col = A[i].col;
                C[k].value = A[i].value + B[j].value;
                k++;
            }

            i++;
            j++;
        }

        else if(A[i].row < B[j].row ||
               (A[i].row == B[j].row && A[i].col < B[j].col)){

            C[k] = A[i];
            k++;
            i++;
        }

        else{
            C[k] = B[j];
            k++;
            j++;
        }
    }

    while(i<n1){
        C[k] = A[i];
        k++;
        i++;
    }

    while(j<n2){
        C[k] = B[j];
        k++;
        j++;
    }

    *n3 = k;
}

int main(){

    entry A[100];
    entry B[100];
    entry C[200];

    int n1 = 0;
    int n2 = 0;
    int n3 = 0;
    int opcode = 0;

    while(1){

        printf("\nA");
        display(A,n1);

        printf("\nB");
        display(B,n2);

        printf("\nC");
        display(C,n3);

        printf("\nSelect action : \
        \n1 input matrix A\
        \n2 input matrix B\
        \n3 add A and B\
        \n4 display A\
        \n5 display B\
        \n6 display C\
        \n7 exit\
        \n\t\t:");

        scanf("%d",&opcode);

        switch(opcode)
        {
        case 1:
            inputmatrix(A,&n1);
            sortmatrix(A,n1);
            break;

        case 2:
            inputmatrix(B,&n2);
            sortmatrix(B,n2);
            break;

        case 3:
            addmatrix(A,n1,B,n2,C,&n3);
            printf("\nMatrix A and B added into C\n");
            break;

        case 4:
            display(A,n1);
            break;

        case 5:
            display(B,n2);
            break;

        case 6:
            display(C,n3);
            break;

        case 7:
            printf("\nprogram exiting\n");
            exit(0);
            break;

        default:
            printf("\nInvalid option");
            break;
        }
    }

    return 0;
}