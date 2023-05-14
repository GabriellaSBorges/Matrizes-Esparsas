#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "list.h"

#define QTY_ALLOC_INITIALLY 10

typedef struct Matrix Matrix;
typedef Matrix* Matrix_pt;


Matrix_pt *matrix_construct(Matrix_pt *matrix);

Matrix_pt *alloc_and_realloc_matrices(Matrix_pt *matrix, int qty_matrices);

Matrix_pt *initialize_matrix(Matrix_pt *matrix, int l, int c);

void verify_matrix(Matrix_pt *matrix);

void matrix_destroy(Matrix_pt *matrix);

void assign_value_matrix(Matrix_pt *matrix);

int matrix_return_index(Matrix_pt *matrix);

int matrix_return_position(Matrix_pt *matrix, int index, char position_type);

void read_node_value_matrix(Matrix_pt *matrix);



#endif