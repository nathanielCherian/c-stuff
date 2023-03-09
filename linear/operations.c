#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"

void print_matrix(Matrix *mat) {
    int m = mat->m;
    int n = mat->n;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f ", mat->vals[i][j]);
        }
        printf("\n");
    }

}

void free_matrix(Matrix *mat) {
    for (int i = 0; i < mat->m; i++) {
        free(mat->vals[i]);
    }
    free(mat->vals);
    free(mat);
}

void free_vector(Vector *vector) {
    free(vector->vals);
    free(vector);
}

Matrix* create_matrix(int m, int n) {
    Matrix *mat = malloc(sizeof(Matrix));
    mat->vals = malloc(m * sizeof(float*));
    for (int i = 0; i < m; i++) {
        mat->vals[i] = malloc(n * sizeof(float));
    }
    mat->m = m;
    mat->n = n;
    return mat;
}

Vector* create_vector(int m) {
    Vector *vector = malloc(sizeof(Vector));
    vector->vals = malloc(m * sizeof(float));
    return vector;
}

Matrix* clone_matrix(Matrix *old_mat) {
    Matrix *new_mat = create_matrix(old_mat->m, old_mat->n);
    for (int i = 0; i < new_mat->m; i++) {
        memcpy(new_mat->vals[i], old_mat->vals[i], new_mat->n * sizeof(float));
    }
    return new_mat;
}

Matrix* load_matrix(char *file_name) {
    assert(file_name != NULL);
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        return NULL;
    }

    int status = 1;
    int m = 0;
    int n = 0;
    status = fscanf(fp, "%d %d", &m, &n);
    if (status != 2) {
        return NULL;
    }
    Matrix *mat = create_matrix(m, n);

    float num = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            status = fscanf(fp, "%f", &num);
            if (status != 1) {
                return NULL;
            }
            mat->vals[i][j] = num;
        }
    }
    return mat;
}


/**
 * Adds two rows
 * row_1: Row to store the output in
 * row_2: Row to add to row_1
 * return: pointer to row_1
 */
float *add_rows(float* row_1, float *row_2, int n) {
    for (int i = 0; i < n; i++) {
        row_1[i] += row_2[i];
    }
    return row_1;
} /* add_rows() */


/**
 * Scales two rows
 * row_1: row to mutate
 * scale: number to scale by
 * return: mutated row
 */
float *scale_row(float *row, float scale, int n) {
    for (int i = 0; i < n; i++) {
        row[i] *= scale;
    }
    return row;
} /* scale_row() */

/**
 * Adds two matricies
 * matrix_1: Matrix to mutate
 * matrix_2: Matrix to add to first one
 * return: pointer to mutated matrix
 */
Matrix* add_matrices(Matrix *matrix_1, Matrix *matrix_2) {
    for (int i = 0; i < matrix_1->m; i++) {
        matrix_1->vals[i] = add_rows(matrix_1->vals[i], matrix_2->vals[i], matrix_1->n);
    }
    return matrix_1;
} /* add_matrices() */


Matrix* scale_matrix(Matrix *matrix, float scale) {
    for (int i = 0; i < matrix->m; i++) {
        matrix->vals[i] = scale_row(matrix->vals[i], scale, matrix->n);
    }
    return matrix;
}

Matrix* swap_rows(Matrix *matrix, int r1, int r2) {
    assert(r1 < matrix->m);
    assert(r2 < matrix->m);
    float *r2_p = matrix->vals[r2];
    matrix->vals[r2] = matrix->vals[r1];
    matrix->vals[r1] = r2_p;
    return matrix;
}
