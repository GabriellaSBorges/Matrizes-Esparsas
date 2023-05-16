#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "list.h"

#define QTY_ALLOC_INITIALLY 10

typedef struct Matrix Matrix;
typedef Matrix* Matrix_pt;



Matrix **matrix_construct(Matrix **matrix, int qty_lines, int qty_columns);

Matrix **alloc_and_realloc_matrix(Matrix **matrix, int qty_matrices);

Matrix **initialize_matrix(Matrix **matrix, int l, int c);

void verify_matrix(Matrix **matrix);

void matrix_destroy(Matrix **matrix);

Matrix **matrix_assign_value(Matrix **matrix, int index, int l, int c, data_type val);

int matrix_return_index(Matrix **matrix);

int matrix_return_position(Matrix **matrix, int index, char position_type);

void matrix_read_value(Matrix *matrix, int index, int l, int c);

void add_matrices(Matrix **matrix, int index_1, int index_2);

void matrix_multiply_by_scalar(Matrix *matrix, data_type scalar);

void multiply_matrices(Matrix **matrix, int index_1, int index_2);







void print_dense_matrix(Matrix *matrix);


#endif