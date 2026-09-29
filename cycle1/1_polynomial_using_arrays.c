#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int exp;
    int cof;
} polynomial;

void displayterm(polynomial t) {
    printf("%dx^%d", t.cof, t.exp);
}

void display(polynomial P[], int n) {
    if (n == 0) {
        printf("Empty polynomial\n");
        return;
    }
    printf("Polynomial : ");
    for (int i = 0; i < n; i++) {
        displayterm(P[i]);
        if (i != n - 1)
            printf(" + ");
    }
    printf("\n");
}

int inputPolynomial(polynomial P[]) {
    int n;
    printf("Enter number of terms: ");
    scanf("%d", &n);

    if (n > MAX) {
        printf("Too many terms!\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        printf("\nTerm %d\n", i + 1);
        printf("Enter exponent: ");
        scanf("%d", &P[i].exp);
        printf("Enter coefficient: ");
        scanf("%d", &P[i].cof);
    }
    return n;
}

void sortPolynomial(polynomial P[], int n) {
    for (int i = 1; i < n; i++) {
        polynomial key = P[i];
        int j = i - 1;
        while (j >= 0 && P[j].exp < key.exp) {
            P[j + 1] = P[j];
            j--;
        }
        P[j + 1] = key;
    }
}

int reducePolynomial(polynomial P[], int n) {
    if (n == 0)
        return 0;

    int newSize = 0;
    for (int i = 0; i < n; i++) {
        if (newSize > 0 && P[newSize - 1].exp == P[i].exp) {
            P[newSize - 1].cof += P[i].cof;
        }
        else {
            P[newSize] = P[i];
            newSize++;
        }
    }   
    return newSize;
}

int addPolynomials(polynomial A[], int nA,polynomial B[], int nB,polynomial C[]) {
    int nC = 0;

    for (int i = 0; i < nA; i++) {
        C[nC++] = A[i];
    }

    for (int i = 0; i < nB; i++) {
        C[nC++] = B[i];
    }

    sortPolynomial(C, nC);
    nC = reducePolynomial(C, nC);
    return nC;
}

int main() {
    polynomial A[MAX];
    polynomial B[MAX];
    polynomial C[2 * MAX];
    int nA, nB, nC;

    printf("========== Polynomial A ==========\n");
    nA = inputPolynomial(A);
    display(A, nA);

    printf("\n\n========== Polynomial B ==========\n");
    nB = inputPolynomial(B);
    display(B, nB);

    nC = addPolynomials(A, nA, B, nB, C);
    printf("\n\n========== Result ==========\n");
    display(C, nC);
    return 0;
}