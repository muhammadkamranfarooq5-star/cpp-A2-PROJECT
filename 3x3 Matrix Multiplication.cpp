#include <iostream>
using namespace std;

const int row = 3;
const int col = 3;

// Function declarations
void inputMatrix(int A[row][col]);
void multiplyMatrix(int A[row][col], int B[row][col], int C[row][col]);
void displayMatrix(int A[row][col]);

int main() {
    int A[row][col], B[row][col], C[row][col];

    cout << "Enter the values for matrix A:" << endl;
    inputMatrix(A);

    cout << "Enter the values for matrix B:" << endl;
    inputMatrix(B);

    // Function call for Multiplication
    multiplyMatrix(A, B, C);

    cout << "Result of A x B is:" << endl;
    displayMatrix(C);

    return 0;
}

// Function for input Matrix
void inputMatrix(int A[row][col]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << "Enter value [" << i << "][" << j << "]: ";
            cin >> A[i][j];
        }
    }
}

// Function to Multiply matrix
void multiplyMatrix(int A[row][col], int B[row][col], int C[row][col]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            C[i][j] = 0;
            for (int k = 0; k < col; k++) {
                C[i][j] = C[i][j] + (A[i][k] * B[k][j]);
            }
        }
    }
}

// Function to display Matrix
void displayMatrix(int A[row][col]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}
