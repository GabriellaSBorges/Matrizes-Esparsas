#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "list.h"

#define QTY_ALLOC_INITIALLY 10
#define PATH_FILE "matrix.bin"

typedef struct Matrix Matrix;
typedef Matrix* Matrix_pt;



Matrix **matrix_construct(Matrix **matrix, int qty_lines, int qty_columns);

Matrix *construct_one_matrix(int qty_lines, int qty_columns);

Matrix **alloc_and_realloc_matrix(Matrix **matrix, int qty_matrices);

Matrix **initialize_matrix(Matrix **matrix, int l, int c);

void verify_matrix(Matrix **matrix);

void matrices_destroy(Matrix **matrix);

void destroy_one_matrix(Matrix **matrix, int index);

void matrix_assign_value(Matrix *matrix, int l, int c, data_type val);

int matrix_return_index(Matrix **matrix);

int matrix_return_position(Matrix **matrix, int index, char position_type);

void matrix_read_value(Matrix *matrix, int index, int l, int c);

void add_matrices(Matrix **matrix, int index_1, int index_2);

void matrix_multiply_by_scalar(Matrix *matrix, data_type scalar);

void matrices_multiply(Matrix **matrix, int index_1, int index_2);

void multiply_point_to_point(Matrix **matrix, int index_1, int index_2);

void matrix_swap_columns(Matrix *matrix, int index_1, int index_2, char list_type);

void matrix_swap_lines(Matrix *matrix, int index_1, int index_2, char list_type);

void matrix_slice(Matrix **matrix, int index, int start_line, int start_column, int end_line, int end_column);

void matrix_transposed(Matrix **matrix, int index);

void matrix_convolution(Matrix **matrix, int index_matrix, Matrix **kernel, int index_kernel);

void print_dense_matrix(Matrix *matrix);

void print_sparse_matrix(Matrix *matrix);


void save_binary_matrix(Matrix *matrix);

void read_binary_matrix(Matrix **matrix);




#endif