#include <stdio.h>
#define MAX 100

void merge(int a[], int low, int mid, int high) {
    int temp[MAX], i = low, j = mid + 1, k = low;
    while (i <= mid && j <= high) {
        if (a[i] <= a[j]) temp[k++] = a[i++];
        else temp[k++] = a[j++];
    }
    while (i <= mid) temp[k++] = a[i++];
    while (j <= high) temp[k++] = a[j++];
    for (i = low; i <= high; i++) a[i] = temp[i];
}

void mergeSort(int a[], int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}

void display(int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int a[MAX], n = 0, choice, i;
    do {
        printf("\n1. Enter Array\n2. Merge Sort\n3. Display Array\n4. Exit\nEnter choice: ");
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
                    mergeSort(a, 0, n - 1);
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