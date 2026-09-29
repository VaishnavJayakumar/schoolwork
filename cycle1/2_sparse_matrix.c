#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
  int row;
  int col;
  float value;
} term;

term createterm(int given_row, int given_col, float given_value) {
  term t;

  t.row = given_row;
  t.col = given_col;
  t.value = given_value;

  return t;
}

void swap(term* a, term* b) {
  term temp = *a;
  *a = *b;
  *b = temp;
}

void insertionSort(term A[], int n) {
  int i, j;
  term key;
  for (i = 1; i < n; i++) {
    key = A[i];
    j = i - 1;
    while (j >= 0 && (A[j].row > key.row || (A[j].row == key.row && A[j].col > key.col))) {
      A[j + 1] = A[j];
      j--;
    }
    A[j + 1] = key;
  }
}

void displaySparse(term A[], int n) {
  if (n == 0) {
    printf("Empty sparse matrix\n");
    return;
  }

  printf("\nSparse Matrix Representation:\n");
  printf("Row\tColumn\tValue\n");

  for (int i = 0; i < n; i++) {
    printf("%d\t%d\t%.2f\n", A[i].row, A[i].col, A[i].value);
  }
}

void displayMatrix(term A[], int n, int rows, int cols) {
  printf("\nMatrix:\n");

  int k = 0;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (k < n && A[k].row == i && A[k].col == j) {
        printf("%6.2f ", A[k].value);
        k++;
      } else {
        printf("%6.2f ", 0.0);
      }
    }

    printf("\n");
  }
}

void transpose(term A[], term B[], int n) {
  for (int i = 0; i < n; i++) {
    B[i].row = A[i].col;
    B[i].col = A[i].row;
    B[i].value = A[i].value;
  }

  insertionSort(B, n);
}

int promptMatrix(term A[], int rows, int cols) {
  int n;
  int row, col;
  float value;

  printf("\nEnter number of non-zero elements: ");
  scanf("%d", &n);

  if (n > MAX) {
    printf("Maximum number of terms is %d\n", MAX);
    return 0;
  }

  for (int i = 0; i < n; i++) {
    printf("\nEnter row index: ");
    scanf("%d", &row);

    printf("Enter column index: ");
    scanf("%d", &col);

    printf("Enter value: ");
    scanf("%f", &value);

    if (row < 0 || row >= rows || col < 0 || col >= cols) {
      printf("Invalid row/column index\n");
      i--;
      continue;
    }

    if (value == 0) {
      printf("Value must be non-zero\n");
      i--;
      continue;
    }

    A[i] = createterm(row, col, value);
  }

  insertionSort(A, n);
  return n;
}

int main() {
  term A[MAX];
  term B[MAX];

  int rows = 0;
  int cols = 0;

  int nA = 0;
  int nB = 0;

  int opcode = 0;

  while (1) {
    printf("\n====================================\n");

    printf("\nMatrix A:\n");

    if (nA == 0) {
      printf("Empty matrix\n");
    } else {
      displayMatrix(A, nA, rows, cols);
    }

    printf("\nMatrix B (Transpose):\n");

    if (nB == 0) {
      printf("Empty matrix\n");
    } else {
      displayMatrix(B, nB, cols, rows);
    }

    printf("\n====================================");

    printf("\nSelect action :\n");
    printf("1. Create sparse matrix A\n");
    printf("2. Display sparse representation of A\n");
    printf("3. Transpose A\n");
    printf("4. Display sparse representation of transpose\n");
    printf("5. Display normal matrix A\n");
    printf("6. Display normal transpose matrix\n");
    printf("7. Exit\n");
    printf("\n\t\t:");

    scanf("%d", &opcode);

    switch (opcode) {
      case 1:
        printf("\nEnter number of rows: ");
        scanf("%d", &rows);
        printf("Enter number of columns: ");
        scanf("%d", &cols);
        if (rows <= 0 || cols <= 0) {
          printf("Invalid matrix dimensions\n");
          rows = 0;
          cols = 0;
          break;
        }
        nA = promptMatrix(A, rows, cols);
        nB = 0;
        printf("\nSparse matrix A created successfully\n");
        break;

      case 2:
        displaySparse(A, nA);
        break;

      case 3:
        if (nA == 0) {
          printf("\nMatrix A is empty\n");
          break;
        }
        transpose(A, B, nA);
        nB = nA;
        printf("\nMatrix transposed successfully\n");
        break;

      case 4:
        if (nB == 0) {
          printf("\nTranspose has not been created yet\n");
          break;
        }
        displaySparse(B, nB);
        break;

      case 5:
        if (nA == 0) {
          printf("\nMatrix A is empty\n");
          break;
        }
        displayMatrix(A, nA, rows, cols);
        break;

      case 6:
        if (nB == 0) {
          printf("\nTranspose has not been created yet\n");
          break;
        }
        displayMatrix(B, nB, cols, rows);
        break;

      case 7:
        printf("\nProgram exiting\n");
        exit(0);

      default:
        printf("\nInvalid option\n");
        break;
    }
  }

  return 0;
}