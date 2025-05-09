#include "algebra.h"
#include <stdio.h>
#include <math.h>

Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    return m;
}

Matrix add_matrix(Matrix a, Matrix b)
{
    // ToDo
    if (a.rows != b.rows || a.cols != b.cols) {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
    return create_matrix(0, 0);
    }
    Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return result;
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    // ToDo
    if (a.rows != b.rows || a.cols != b.cols) {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
    return create_matrix(0, 0);
    }
    Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] - b.data[i][j];
        }
    }
    return result;
}


Matrix mul_matrix(Matrix a, Matrix b)
{
    // ToDo
    if (a.cols != b.rows) {
        printf("Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n");
    return create_matrix(0, 0);
    }
    Matrix result = create_matrix(a.rows, b.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < b.cols; j++) {
            result.data[i][j] = 0;
            for (int k = 0; k < a.cols; k++) {
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    return result;
}

Matrix scale_matrix(Matrix a, double k)
{
    // ToDo

    Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] * k;
        }
    }
    return result;
}

Matrix transpose_matrix(Matrix a)
{
    // ToDo
    Matrix result = create_matrix(a.cols, a.rows);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[j][i] = a.data[i][j];
        }
    }
    return result;
}

double det_matrix(Matrix a)
{
    // ToDo
    if (a.rows != a.cols) {
        printf("Error: The matrix must be a square matrix.\n");
    return 0;
    }
    int n = a.rows;
    if (n == 1) return a.data[0][0];
    
    double det = 0;
    int sign = 1;
    for (int j = 0; j < n; j++) {
        Matrix submat = create_matrix(n-1, n-1);
        for (int row = 1; row < n; row++) {
            int sub_col = 0;
            for (int col = 0; col < n; col++) {
                if (col == j) continue;
                submat.data[row-1][sub_col++] = a.data[row][col];
            }
        }
        det += sign * a.data[0][j] * det_matrix(submat);
        sign *= -1;
    }
    return det;
}

Matrix inv_matrix(Matrix a)
{
    // ToDo
    if (a.rows != a.cols) {
        printf("Error: The matrix must be a square matrix.\n");
    return create_matrix(0, 0);
    }
    int n = a.rows;
    double det = det_matrix(a);
    if (fabs(det) < 1e-6) {
        printf("Error: The matrix is singular.\n");
        return create_matrix(0, 0);
    }
    
    // Augmented matrix setup
    double aug[MAX_MATRIX_SIZE][2*MAX_MATRIX_SIZE] = {{0}};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) aug[i][j] = a.data[i][j];
        aug[i][i + n] = 1.0;
    }
    
    // Gauss-Jordan elimination
    for (int i = 0; i < n; i++) {
        // Find pivot
        int max_row = i;
        for (int k = i; k < n; k++) {
            if (fabs(aug[k][i]) > fabs(aug[max_row][i])) max_row = k;
        }
        if (fabs(aug[max_row][i]) < 1e-6) {
            printf("Error: The matrix is singular.\n");
            return create_matrix(0, 0);
        }
        // Swap rows
        if (max_row != i) {
            for (int j = 0; j < 2*n; j++) {
                double tmp = aug[i][j];
                aug[i][j] = aug[max_row][j];
                aug[max_row][j] = tmp;
            }
        }
        // Normalize pivot row
        double pivot = aug[i][i];
        for (int j = 0; j < 2*n; j++) aug[i][j] /= pivot;
        // Eliminate other rows
        for (int k = 0; k < n; k++) {
            if (k == i) continue;
            double factor = aug[k][i];
            for (int j = 0; j < 2*n; j++) aug[k][j] -= factor * aug[i][j];
        }
    }
    
    // Extract inverse matrix
    Matrix inv = create_matrix(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) inv.data[i][j] = aug[i][j + n];
    }
    return inv;
}

int rank_matrix(Matrix a)
{
    int rank = 0;
    double mat[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
    for (int i = 0; i < a.rows; i++)
        for (int j = 0; j < a.cols; j++)
            mat[i][j] = a.data[i][j];
    
    for (int col = 0; col < a.cols && rank < a.rows; col++) {
        int pivot = -1;
        for (int i = rank; i < a.rows; i++) {
            if (fabs(mat[i][col]) > 1e-6) {
                pivot = i;
                break;
            }
        }
        if (pivot == -1) continue;
        
        // Swap rows
        for (int j = col; j < a.cols; j++) {
            double tmp = mat[rank][j];
            mat[rank][j] = mat[pivot][j];
            mat[pivot][j] = tmp;
        }
        // Eliminate rows below
        for (int i = rank + 1; i < a.rows; i++) {
            double factor = mat[i][col] / mat[rank][col];
            for (int j = col; j < a.cols; j++)
                mat[i][j] -= factor * mat[rank][j];
        }
        rank++;
    }
    return rank;
}

    

double trace_matrix(Matrix a)
{
    // ToDo
    if (a.rows != a.cols) {
        printf("Error: The matrix must be a square matrix.\n");
    return 0;
    }
    double trace = 0;
    for (int i = 0; i < a.rows; i++) trace += a.data[i][i];
    return trace;
}

void print_matrix(Matrix a)
{
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            // 按行打印，每个元素占8个字符的宽度，小数点后保留2位，左对齐
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}