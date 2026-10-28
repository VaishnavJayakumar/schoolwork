
#include <stdio.h>

int main() {
    int a[100], n = 0, choice, value, i, j, temp;
    int low, high, mid, first, last;

    while (1) {
        printf("\n1. Add Element\n2. Display Sorted Array\n3. Search Element\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (n == 100) {
                    printf("Array is full\n");
                    break;
                }
                printf("Enter element: ");
                scanf("%d", &a[n]);
                n++;

                for (i = n - 1; i > 0 && a[i] < a[i - 1]; i--) {
                    temp = a[i];
                    a[i] = a[i - 1];
                    a[i - 1] = temp;
                }
                break;

            case 2:
                if (n == 0) {
                    printf("Array is empty\n");
                    break;
                }
                for (i = 0; i < n; i++)
                    printf("%d ", a[i]);
                printf("\n");
                break;

            case 3:
                if (n == 0) {
                    printf("Array is empty\n");
                    break;
                }

                printf("Enter element to search: ");
                scanf("%d", &value);

                low = 0;
                high = n - 1;
                first = -1;

                while (low <= high) {
                    mid = low + (high - low) / 2;

                    if (a[mid] >= value) {
                        if (a[mid] == value)
                            first = mid;
                        high = mid - 1;
                    } else {
                        low = mid + 1;
                    }
                }

                if (first == -1) {
                    printf("Element not found\n");
                    break;
                }

                low = first;
                high = n - 1;
                last = first;

                while (low <= high) {
                    mid = low + (high - low) / 2;

                    if (a[mid] <= value) {
                        if (a[mid] == value)
                            last = mid;
                        low = mid + 1;
                    } else {
                        high = mid - 1;
                    }
                }

                printf("Element found from position %d to %d\n", first + 1, last + 1);
                printf("Total occurrences: %d\n", last - first + 1);
                break;

            case 4:
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }
}
