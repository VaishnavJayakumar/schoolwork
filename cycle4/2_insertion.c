#include <stdio.h>
#define MAX 100

void insertionSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
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
        printf("\n1. Enter Array\n2. Insertion Sort\n3. Display Array\n4. Exit\nEnter choice: ");
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
                    insertionSort(a, n);
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