#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "matrix.h"


/*
 * This functions puts a matrix in row echlon form (upper triangular)
 * It keeps track of the number of swaps made
 */
Matrix* row_echlon_swaps(Matrix *matrix, int *num_swaps) {
    int n = matrix->n;
    int pivot_col = 0;
    for (int m = 0; m < matrix->m; m++) {

        // If we have no more columns to look at, just return what we have
        if (pivot_col >= matrix->n) {
            return matrix;
        }

        // We need to make sure that the pivot is non-zero, else we swap
        for (int i = m+1; i < matrix->m; i++) {
            //printf("%f %d %d\n", matrix->vals[m][pivot_col], m, pivot_col);
            if (matrix->vals[m][pivot_col] == 0) {
                // printf("%d SWAP %d\n", m, i);
                // Need to swap rows and continue
                swap_rows(matrix, m, i);
                (*num_swaps)++;
            } else {
                // We found the right row to continue, exit this 
                break;
            }
        }

        // Even after all that swapping, if we still aren't good...
        if (matrix->vals[m][pivot_col] == 0) {
            //printf("advancing pivot column\n");
            pivot_col++; // move on to the next column
            m--;
            continue; // lets try this again on the same row
        }

        // At this point we know that the pivot should be non-zero
        float *row = matrix->vals[m];
        float pivot = row[pivot_col];
        //printf("%d %d: %f\n", pivot_col, m, pivot);
        for (int m1 = m+1; m1 < matrix->m; m1++) {
            float *below_row = matrix->vals[m1];
            float scale = below_row[m] / pivot;
            if (scale != 0) {
                scale_row(row, -scale, n);
                add_rows(below_row, row, n); 
                scale_row(row, -1/scale, n);
            }
        }
        pivot_col++; // Advance pivot column
    }
    return matrix;
}


/**
 * Wrapper for row_echlon_swaps
 */
Matrix* row_echlon_form(Matrix *matrix) {
    int n = 0;
    return row_echlon_swaps(matrix, &n);
}



Matrix* rref(Matrix * matrix) {
    row_echlon_form(matrix);
    // Start at the last row
    for (int m = matrix->m-1; m >= 0; m--) {
        float *row = matrix->vals[m];
        float pivot = 0;
        // Find the pivot
        for (int n = 0; n < matrix->n; n++) {
            if (row[n] == 0) {
                continue; 
            }
            pivot = row[n];
            // Loop through all the preceding matrices
            for (int m1 = m-1; m1 >= 0; m1--) {
                float *above_row = matrix->vals[m1];
                float scale = above_row[n] / row[n];
                if (scale != 0) {
                    scale_row(row, -scale, matrix->n);
                    add_rows(above_row, row, matrix->n);
                    scale_row(row, -1/scale, matrix->n);
                }
            }
            break;
        }
        if (pivot != 0) {
            scale_row(row, 1/pivot, matrix->n);
        }
    }
    return matrix;
}

Matrix *inverse_matrix(Matrix *matrix) {
    assert(matrix != NULL);
    if (matrix->m != matrix->n) {
        return NULL;
    } 
    Matrix *aug_matrix = create_matrix(matrix->m, 2*matrix->n);
    for (int i = 0; i < matrix->m; i++) {
        memcpy(aug_matrix->vals[i], matrix->vals[i], matrix->n*sizeof(float));
        aug_matrix->vals[i][matrix->n + i] = 1.0;
    }
    rref(aug_matrix);
    print_matrix(aug_matrix);
    for (int i = 0; i < matrix->m; i++) {
        if (fabs(aug_matrix->vals[i][i] - 1.0) > 1e-6) {
            return NULL;
        }
    }
    for (int i = 0; i < matrix->m; i++) {
        memcpy(matrix->vals[i], &aug_matrix->vals[i][matrix->n], matrix->n * sizeof(float));
    }

    free_matrix(aug_matrix);
    return matrix;
}

float determinant(Matrix *matrix) {
    assert(matrix != NULL);
    if (matrix->m != matrix->n) {
        return 0;
    }
    Matrix *matrix_copy = clone_matrix(matrix);
    int num_swaps = 0;
    row_echlon_swaps(matrix_copy, &num_swaps);
    //printf("%d\n", num_swaps);
    float determinant = pow(-1, num_swaps);
    for (int i = 0; i < matrix->m; i++) {
        determinant *= matrix_copy->vals[i][i];
    }
    free_matrix(matrix_copy);
    return determinant;
}


int main() {
    Matrix *mat1 = load_matrix("m1.txt");
    //inverse_matrix(mat1);
//    row_echlon_form(mat1);
    print_matrix(mat1);
    inverse_matrix(mat1);
    print_matrix(mat1);
    rref(mat1);
    print_matrix(mat1);
}
int mfain() {
    Matrix *mat_1 = load_matrix("m4.txt");
    Matrix *mat_2 = load_matrix("m2.txt");
    print_matrix(mat_1);
    printf("\n");
    /*
    print_matrix(mat_2);
    printf("\n");*/
    rref(mat_1);
    print_matrix(mat_1);
    /*
    scale_matrix(mat_2, 2.0);
    add_matrices(mat_1, mat_2);
    print_matrix(mat_1);
    printf("\n");
    print_matrix(mat_2);
    printf("\n");
    */
    free(mat_1);
    free(mat_2);
}
