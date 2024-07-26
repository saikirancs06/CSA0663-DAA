#include <stdio.h>

#define SIZE 2

// Function to add two matrices
void addMatrix(int a[SIZE][SIZE], int b[SIZE][SIZE], int result[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

// Function to subtract two matrices
void subtractMatrix(int a[SIZE][SIZE], int b[SIZE][SIZE], int result[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = a[i][j] - b[i][j];
        }
    }
}

// Function to perform Strassen's matrix multiplication
void strassenMatrixMultiplication(int a[SIZE][SIZE], int b[SIZE][SIZE], int result[SIZE][SIZE]) {
    int m1[SIZE][SIZE], m2[SIZE][SIZE], m3[SIZE][SIZE], m4[SIZE][SIZE], m5[SIZE][SIZE], m6[SIZE][SIZE], m7[SIZE][SIZE];
    int temp1[SIZE][SIZE], temp2[SIZE][SIZE];
    int a11[SIZE][SIZE], a12[SIZE][SIZE], a21[SIZE][SIZE], a22[SIZE][SIZE];
    int b11[SIZE][SIZE], b12[SIZE][SIZE], b21[SIZE][SIZE], b22[SIZE][SIZE];
    int c11[SIZE][SIZE], c12[SIZE][SIZE], c21[SIZE][SIZE], c22[SIZE][SIZE];

    // Split matrices into submatrices
    a11[0][0] = a[0][0]; a11[0][1] = a[0][1];
    a12[0][0] = a[0][1]; a12[0][1] = a[1][1];
    a21[0][0] = a[1][0]; a21[0][1] = a[1][1];
    a22[0][0] = a[1][0]; a22[0][1] = a[1][1];

    b11[0][0] = b[0][0]; b11[0][1] = b[0][1];
    b12[0][0] = b[0][1]; b12[0][1] = b[1][1];
    b21[0][0] = b[1][0]; b21[0][1] = b[1][1];
    b22[0][0] = b[1][0]; b22[0][1] = b[1][1];

    // Compute the 7 products
    addMatrix(a11, a22, temp1);
    addMatrix(b11, b22, temp2);
    strassenMatrixMultiplication(temp1, temp2, m1);

    addMatrix(a21, a22, temp1);
    strassenMatrixMultiplication(temp1, b11, m2);

    subtractMatrix(b12, b22, temp1);
    strassenMatrixMultiplication(a11, temp1, m3);

    subtractMatrix(b21, b11, temp1);
    strassenMatrixMultiplication(a22, temp1, m4);

    addMatrix(a11, a12, temp1);
    strassenMatrixMultiplication(temp1, b22, m5);

    subtractMatrix(a21, a11, temp1);
    addMatrix(b11, b12, temp2);
    strassenMatrixMultiplication(temp1, temp2, m6);

    subtractMatrix(a12, a22, temp1);
    addMatrix(b21, b22, temp2);
    strassenMatrixMultiplication(temp1, temp2, m7);

    // Compute the final submatrices of the result
    addMatrix(m1, m4, temp1);
    subtractMatrix(temp1, m5, temp2);
    addMatrix(temp2, m7, c11);

    addMatrix(m3, m5, c12);

    addMatrix(m2, m4, c21);

    addMatrix(m1, m3, temp1);
    subtractMatrix(temp1, m2, temp2);
    addMatrix(temp2, m6, c22);

    // Combine the submatrices into the result matrix
    result[0][0] = c11[0][0]; result[0][1] = c11[0][1];
    result[1][0] = c21[0][0]; result[1][1] = c21[0][1];
    result[2][0] = c12[0][0]; result[2][1] = c12[0][1];
    result[3][0] = c22[0][0]; result[3][1] = c22[0][1];
}

int main() {
    int a[SIZE][SIZE], b[SIZE][SIZE], result[SIZE][SIZE];

    // User input for the first matrix
    printf("Enter the elements of the first 2x2 matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    // User input for the second matrix
    printf("Enter the elements of the second 2x2 matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            scanf("%d", &b[i][j]);
        }
    }

    // Perform Strassen's matrix multiplication
    strassenMatrixMultiplication(a, b, result);

    // Print the result matrix
    printf("Resultant matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}
