#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct{
    char arr[MAX];
    int top;
}stack;

stack* createstack(){
    stack* s = (stack*)malloc(sizeof(stack));

    if(s == NULL){
        printf("createstack failed\n");
        exit(1);
    }

    s->top = -1;
    return s;
}

void push(stack* s, char ch){
    if(s->top == MAX - 1){
        printf("Stack overflow\n");
        return;
    }

    s->arr[++s->top] = ch;
}

char pop(stack* s){
    if(s->top == -1){
        printf("Stack underflow\n");
        return '\0';
    }

    return s->arr[s->top--];
}

void display(stack* s){
    if(s->top == -1){
        printf("Stack is empty\n");
        return;
    }

    printf("Stack : ");
    for(int i = 0; i <= s->top; i++){
        printf("%c ", s->arr[i]);
    }
    printf("\n");
}

int isPalindrome(char str[]){
    stack* s = createstack();

    int i = 0;

    while(str[i] != '\0'){
        push(s, str[i]);
        i++;
    }

    i = 0;

    while(str[i] != '\0'){
        if(str[i] != pop(s)){
            free(s);
            return 0;
        }
        i++;
    }

    free(s);
    return 1;
}

int main(){

    char str[MAX];

    printf("Enter a string: ");
    scanf("%s", str);

    if(isPalindrome(str)){
        printf("The string is a palindrome\n");
    }else{
        printf("The string is not a palindrome\n");
    }

    return 0;
}