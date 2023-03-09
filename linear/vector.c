#include <stdio.h>
#include <assert.h>
#include "matrix.h"

Vector* vector_mult(Matrix *matrix, Vector *vector) {
    assert(matrix != NULL);
    assert(vector != NULL);
    if (vector->m != matrix->n) {
        return NULL;
    }
    Vector *new_vector = create_vector(matrix->m);

}

