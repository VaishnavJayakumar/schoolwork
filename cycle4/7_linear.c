
#include <stdio.h>

int main() {
    int a[100], n = 0, choice, value, i, found;

    while (1) {
        printf("\n1. Add Element\n2. Display Array\n3. Search Element\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (n == 100) {
                    printf("Array is full\n");
                    break;
                }
                printf("Enter element: ");
                scanf("%d", &a[n++]);
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
                found = 0;
                for (i = 0; i < n; i++) {
                    if (a[i] == value) {
                        printf("Element found at position %d\n", i + 1);
                        found = 1;
                    }
                }
                if (!found)
                    printf("Element not found\n");
                break;

            case 4:
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }
}
