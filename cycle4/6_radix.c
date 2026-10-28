#include <stdio.h>
#define MAX 100

int getMax(int a[], int n) {
    int max = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] > max)
            max = a[i];
    return max;
}

void countingSort(int a[], int n, int exp) {
    int output[MAX], count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(a[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        int digit = (a[i] / exp) % 10;
        output[count[digit] - 1] = a[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++)
        a[i] = output[i];
}

void radixSort(int a[], int n) {
    int max = getMax(a, n);

    for (int exp = 1; max / exp > 0;) {
        countingSort(a, n, exp);
        if (exp > max / 10)
            break;
        exp *= 10;
    }
}

void display(int a[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int a[MAX], n = 0, choice, valid;

    do {
        printf("\n1. Enter Array\n2. Radix Sort\n3. Display Array\n4. Exit\nEnter choice: ");
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

                printf("Enter non-negative integers: ");
                valid = 1;
                for (int i = 0; i < n; i++) {
                    scanf("%d", &a[i]);
                    if (a[i] < 0)
                        valid = 0;
                }

                if (!valid) {
                    printf("Negative numbers are not allowed\n");
                    n = 0;
                }
                break;

            case 2:
                if (n == 0)
                    printf("Enter array first\n");
                else {
                    radixSort(a, n);
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