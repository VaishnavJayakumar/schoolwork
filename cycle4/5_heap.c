#include <stdio.h>
#define MAX 100

void heapify(int a[], int n, int i) {
    int largest = i, left = 2 * i + 1, right = 2 * i + 2, temp;
    if (left < n && a[left] > a[largest]) largest = left;
    if (right < n && a[right] > a[largest]) largest = right;
    if (largest != i) {
        temp = a[i]; a[i] = a[largest]; a[largest] = temp;
        heapify(a, n, largest);
    }
}

void heapSort(int a[], int n) {
    int i, temp;
    for (i = n / 2 - 1; i >= 0; i--) heapify(a, n, i);
    for (i = n - 1; i > 0; i--) {
        temp = a[0]; a[0] = a[i]; a[i] = temp;
        heapify(a, i, 0);
    }
}

void display(int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int a[MAX], n = 0, choice, i;
    do {
        printf("\n1. Enter Array\n2. Heap Sort\n3. Display Array\n4. Exit\nEnter choice: ");
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
                for (i = 0; i < n; i++) scanf("%d", &a[i]);
                break;
            case 2:
                if (n == 0) printf("Enter array first\n");
                else {
                    heapSort(a, n);
                    printf("Array sorted successfully\n");
                }
                break;
            case 3:
                if (n == 0) printf("Array is empty\n");
                else display(a, n);
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