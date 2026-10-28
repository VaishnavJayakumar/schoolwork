#include <stdio.h>
#define MAX 100

int partition(int a[], int low, int high) {
    int pivot = a[high], i = low - 1, j, temp;
    for (j = low; j < high; j++) {
        if (a[j] <= pivot) {
            i++;
            temp = a[i]; a[i] = a[j]; a[j] = temp;
        }
    }
    temp = a[i + 1]; a[i + 1] = a[high]; a[high] = temp;
    return i + 1;
}

void quickSort(int a[], int low, int high) {
    if (low < high) {
        int p = partition(a, low, high);
        quickSort(a, low, p - 1);
        quickSort(a, p + 1, high);
    }
}

void display(int a[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int a[MAX], n = 0, choice, i;
    do {
        printf("\n1. Enter Array\n2. Quick Sort\n3. Display Array\n4. Exit\nEnter choice: ");
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
                for (i = 0; i < n; i++)
                    scanf("%d", &a[i]);
                break;

            case 2:
                if (n == 0)
                    printf("Enter array first\n");
                else {
                    quickSort(a, 0, n - 1);
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