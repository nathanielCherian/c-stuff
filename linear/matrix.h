#define MAX_SIZE 10

struct matrix_struct {
    int m;
    int n;
    float **vals;
};

typedef struct matrix_struct Matrix;

struct vector_struct {
    int m;
    float *vals;
};
typedef struct vector_struct Vector;

#define BAD_MATRIX (Matrix) {-1, -1, {}}

void print_matrix(Matrix *mat);
void free_matrix(Matrix *mat);
void free_vector(Vector *vector);
Matrix* create_matrix(int m, int n);
Vector* create_vector(int m);
Matrix* clone_matrix(Matrix *old_mat);
Matrix* load_matrix(char *file_name);
float* add_rows(float *row_1, float *row_2, int n);
float* scale_row(float *row, float scale, int n);
Matrix* add_matrices(Matrix *matrix_1, Matrix *matrix_2);
Matrix* scale_matrix(Matrix *matrix, float scale);
Matrix* swap_rows(Matrix *matrix, int r1, int r2);

