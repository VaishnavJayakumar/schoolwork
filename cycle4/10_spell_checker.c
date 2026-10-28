#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 101
#define WORD 50
#define MAX 500

typedef struct {
    char word[WORD];
    int occupied;
} Entry;

Entry table[SIZE];
char dictionary[MAX][WORD];
int count = 0;

unsigned int hash(char *word) {
    unsigned int h = 0;
    while (*word)
        h = (h * 31 + tolower((unsigned char)*word++)) % SIZE;
    return h;
}

void normalize(char *word) {
    int i;
    for (i = 0; word[i]; i++)
        word[i] = tolower((unsigned char)word[i]);
}

int search(char *word) {
    unsigned int index = hash(word);
    int start = index;

    while (table[index].occupied) {
        if (strcmp(table[index].word, word) == 0)
            return 1;
        index = (index + 1) % SIZE;
        if (index == start)
            break;
    }

    return 0;
}

void insert(char *word) {
    unsigned int index;
    normalize(word);

    if (search(word)) {
        printf("Word already exists in dictionary.\n");
        return;
    }

    if (count >= MAX) {
        printf("Dictionary is full.\n");
        return;
    }

    index = hash(word);

    while (table[index].occupied)
        index = (index + 1) % SIZE;

    strcpy(table[index].word, word);
    table[index].occupied = 1;
    strcpy(dictionary[count++], word);

    printf("Word added successfully.\n");
}

int distance(char *a, char *b) {
    int dp[WORD][WORD];
    int i, j, m = strlen(a), n = strlen(b);

    for (i = 0; i <= m; i++)
        dp[i][0] = i;

    for (j = 0; j <= n; j++)
        dp[0][j] = j;

    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            int cost = (a[i - 1] != b[j - 1]);
            int x = dp[i - 1][j] + 1;
            int y = dp[i][j - 1] + 1;
            int z = dp[i - 1][j - 1] + cost;

            dp[i][j] = x < y ? x : y;
            if (z < dp[i][j])
                dp[i][j] = z;
        }
    }

    return dp[m][n];
}

void suggest(char *word) {
    int i, d, best = 3, found = 0;

    printf("Suggested corrections:\n");

    for (i = 0; i < count; i++) {
        d = distance(word, dictionary[i]);

        if (d > 0 && d <= 2 && d < best) {
            best = d;
            found = 0;
        }

        if (d > 0 && d == best && d <= 2) {
            printf("%s\n", dictionary[i]);
            found = 1;
        }
    }

    if (!found)
        printf("No suggestions found.\n");
}

void checkWord(void) {
    char word[WORD];

    printf("Enter word: ");
    scanf("%49s", word);
    normalize(word);

    if (search(word))
        printf("'%s' is a valid word.\n", word);
    else {
        printf("'%s' is misspelled.\n", word);
        suggest(word);
    }
}

void display(void) {
    int i;

    if (count == 0) {
        printf("Dictionary is empty.\n");
        return;
    }

    printf("Dictionary words:\n");
    for (i = 0; i < count; i++)
        printf("%s\n", dictionary[i]);
}

int main(void) {
    int choice;
    char word[WORD];

    while (1) {
        printf("\n1. Add word to dictionary\n");
        printf("2. Check spelling\n");
        printf("3. Suggest corrections\n");
        printf("4. Display dictionary\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter word: ");
                scanf("%49s", word);
                insert(word);
                break;

            case 2:
                checkWord();
                break;

            case 3:
                printf("Enter misspelled word: ");
                scanf("%49s", word);
                normalize(word);

                if (search(word))
                    printf("Word is already valid.\n");
                else
                    suggest(word);
                break;

            case 4:
                display();
                break;

            case 5:
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
}