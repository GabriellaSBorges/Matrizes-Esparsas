#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "list.h"

#define QTY_ALLOC_INITIALLY 10

typedef struct Matrix Matrix;
typedef Matrix* Matrix_pt;


void create_matrix(Matrix_pt matrix);

void *matrix_construct(Matrix_pt *matrix, int qty_lines, qty_columns);

void *matrix_alloc_and_realloc(Matrix_pt *matrix, int qty_matrices);

void *matrix_initialize(Matrix_pt *matrix, int l, int c);

void matrix_verify(Matrix_pt *matrix);

void destroy_matrix(Matrix_pt *matrix);

void assign_value_matrix(Matrix_pt *matrix);

int matrix_return_index(Matrix_pt *matrix);

int matrix_return_position(Matrix_pt *matrix, int index, char position_type);

void read_node_value_matrix(Matrix_pt *matrix);



#endif