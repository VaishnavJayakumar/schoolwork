#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define M 26
#define LEN 100

char linear[M][LEN], quadratic[M][LEN];
int usedL[M], usedQ[M];
int method = 1;

int hashcode(char *word) {
    int sum = 0;
    for (int i = 0; word[i]; i++)
        sum += tolower((unsigned char)word[i]);
    return sum % M;
}

void addword(char *word) {
    int key = hashcode(word);

    for (int j = 0; j < M; j++) {
        int i = method == 1 ? (key + j) % M
                            : (key + j * j) % M;

        int *used = method == 1 ? usedL : usedQ;
        char (*table)[LEN] = method == 1 ? linear : quadratic;

        if (used[i]) {
            if (strcmp(table[i], word) == 0)
                return;
        } else {
            strcpy(table[i], word);
            used[i] = 1;
            return;
        }
    }

    printf("Insertion failed\n");
}

void display(void) {
    int *used = method == 1 ? usedL : usedQ;
    char (*table)[LEN] = method == 1 ? linear : quadratic;

    for (int i = 0; i < M; i++)
        if (used[i])
            printf("%d : %s\n", i, table[i]);
        else
            printf("%d : Empty\n", i);
}

void searchword(char *word) {
    int key = hashcode(word), comparisons = 0;
    int *used = method == 1 ? usedL : usedQ;
    char (*table)[LEN] = method == 1 ? linear : quadratic;

    for (int j = 0; j < M; j++) {
        int i = method == 1 ? (key + j) % M
                            : (key + j * j) % M;

        if (!used[i])
            break;

        comparisons++;

        if (strcmp(table[i], word) == 0) {
            printf("Word found at index %d\n", i);
            printf("Key comparisons: %d\n", comparisons);
            return;
        }
    }

    printf("Word not found\n");
    printf("Key comparisons: %d\n", comparisons);
}

int main(void) {
    char text[1000], word[LEN], target[LEN];
    int choice, i, j;

    while (1) {
        printf("\n1. Select collision resolution technique\n");
        printf("2. Enter text and build hash table\n");
        printf("3. Add word\n");
        printf("4. Display hash table\n");
        printf("5. Search word\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("1. Linear probing\n");
                printf("2. Quadratic probing\n");
                printf("Enter method: ");
                scanf("%d", &method);
                if (method != 1 && method != 2) {
                    method = 1;
                    printf("Invalid method\n");
                }
                break;

            case 2:
                for (i = 0; i < M; i++) {
                    usedL[i] = 0;
                    usedQ[i] = 0;
                }

                printf("Enter text: ");
                getchar();
                fgets(text, sizeof(text), stdin);

                i = 0;
                while (text[i]) {
                    while (text[i] && !isalpha((unsigned char)text[i]))
                        i++;

                    j = 0;
                    while (text[i] && isalpha((unsigned char)text[i])) {
                        if (j < LEN - 1)
                            word[j++] = tolower((unsigned char)text[i]);
                        i++;
                    }
                    word[j] = '\0';

                    if (j > 0)
                        addword(word);
                }
                break;

            case 3:
                printf("Enter word: ");
                scanf("%99s", word);
                for (i = 0; word[i]; i++)
                    word[i] = tolower((unsigned char)word[i]);
                addword(word);
                break;

            case 4:
                display();
                break;

            case 5:
                printf("Enter word to search: ");
                scanf("%99s", target);
                for (i = 0; target[i]; i++)
                    target[i] = tolower((unsigned char)target[i]);
                searchword(target);
                break;

            case 6:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }
}