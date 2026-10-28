#include <stdio.h>
#define MAX 100

void selectionSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[min])
                min = j;

        int temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
}

void display(int a[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int a[MAX], n = 0, choice;

    do {
        printf("\n1. Enter Array\n2. Selection Sort\n3. Display Array\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter number of elements: ");
                scanf("%d", &n);
                if (n < 1 || n > MAX) {
                    printf("Invalid size\n");
                    n = 0;
                    break;
                }
                printf("Enter elements: ");
                for (int i = 0; i < n; i++)
                    scanf("%d", &a[i]);
                break;

            case 2:
                if (n == 0)
                    printf("Enter array first\n");
                else {
                    selectionSort(a, n);
                    printf("Array sorted successfully\n");
                }
                break;

            case 3:
                if (n == 0)
                    printf("Array is empty\n");
                else
                    display(a, n);
                break;

            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice\n");
        }
    } while (choice != 4);

    return 0;
}