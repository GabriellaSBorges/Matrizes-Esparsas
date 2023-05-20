#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "list.h"

#define PATH_FILE "matrix.bin"

typedef struct Matrix Matrix;


Matrix *matrix_construct(int *qty_matrices, int qty_lines, int qty_columns);

void matrix_destroy(Matrix *matrix);

void matrix_assign_value(Matrix *matrix, int l, int c, data_type val);

// int matrix_return_index(Matrix **matrix);

// int matrix_return_position(Matrix **matrix, int index, char position_type);

void matrix_read_value(Matrix *matrix, int index, int l, int c);

Matrix *add_matrices(Matrix *matrix_1, Matrix *matrix_2, int *qty_matrices);

Matrix *matrix_multiply_by_scalar(Matrix *matrix, int *qty_matrices, data_type scalar);

Matrix *matrices_multiply(Matrix *matrix_1, Matrix *matrix_2, int *qty_matrices);

Matrix *multiply_point_to_point(Matrix *matrix_1, Matrix *matrix_2, int *qty_matrices);

void matrix_swap_columns(Matrix *matrix, int index_1, int index_2, char list_type);

void matrix_swap_lines(Matrix *matrix, int index_1, int index_2, char list_type);

Matrix *matrix_slice(Matrix *matrix, int *qty_matrices, int start_line, int start_column, int end_line, int end_column);

Matrix *matrix_transposed(Matrix *matrix, int *qty_matrices);

void matrix_convolution(Matrix *matrix, Matrix *kernel, int *qty_matrices);

void print_dense_matrix(Matrix *matrix);

void print_sparse_matrix(Matrix *matrix);

void save_binary_matrix(Matrix *matrix);

Matrix *read_binary_matrix(int *qty_matrices);


#endif