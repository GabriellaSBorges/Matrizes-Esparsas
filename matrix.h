#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "list.h"

#define QTY_ALLOC_INITIALLY 10

typedef struct Matrix Matrix;
typedef Matrix* Matrix_pt;


// Matrix_pt *create_matrix(Matrix_pt *matrix, int l, int c);

Matrix_pt *matrix_construct(Matrix_pt *matrix, int qty_lines, int qty_columns);

Matrix_pt *matrix_alloc_and_realloc(Matrix_pt *matrix, int qty_matrices);

Matrix_pt *matrix_initialize(Matrix_pt *matrix, int l, int c);

void matrix_verify(Matrix_pt *matrix);

void destroy_matrix(Matrix_pt *matrix);

void assign_value_matrix(Matrix_pt *matrix, int index, int l, int c, data_type val);

int matrix_return_index(Matrix_pt *matrix);

int matrix_return_position(Matrix_pt *matrix, int index, char position_type);

void read_node_value_matrix(Matrix_pt *matrix, int index, int l, int c);

void add_matrices(Matrix_pt *matrix);

// int matrix_return_index_2(Matrix_pt *matrix, int qty_lines, int qty_columns);

void print_dense_matrix(Matrix_pt *matrix, int index);

#endif