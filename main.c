#include "headers/matrix.h"

int main(){
    Matrix **matrix = NULL;

    printf("---------------\n Bem-vindo! :) \n---------------\n");


    matrix = matrix_construct(matrix, 2, 3); // matriz 0
    matrix = matrix_construct(matrix, 2, 3); // matriz 1

    matrix_assign_value(matrix[0], 0, 0, 1); 
    matrix_assign_value(matrix[0], 0, 1, 2); 
    matrix_assign_value(matrix[0], 1, 0, 3); 
    matrix_assign_value(matrix[0], 1, 1, 4); 
    matrix_assign_value(matrix[0], 0, 2, 1); 
    matrix_assign_value(matrix[0], 1, 2, 1); 
    
    // print_sparse_matrix(matrix[0]);
    print_dense_matrix(matrix[0]);

    matrix_assign_value(matrix[1], 0, 0, 5); 
    matrix_assign_value(matrix[1], 0, 1, 6); 
    matrix_assign_value(matrix[1], 1, 0, 7); 
    matrix_assign_value(matrix[1], 1, 1, 8); 
    matrix_assign_value(matrix[1], 0, 2, 0); 
    matrix_assign_value(matrix[1], 1, 2, 0); 

    // print_sparse_matrix(matrix[1]);
    print_dense_matrix(matrix[1]);

    // matrix_read_value(matrix[0], 0, 0, 0); 
    // matrix_read_value(matrix[0], 0, 1, 1); 
    
    add_matrices(matrix, 0, 1); // matriz 2
    print_dense_matrix(matrix[2]);

    // matrix_multiply_by_scalar(matrix[2], 2); // substitui matriz 2
    // print_dense_matrix(matrix[2]);

    // matrices_multiply(matrix, 0, 1); // matriz 3
    // print_dense_matrix(matrix[3]);

    // multiply_point_to_point(matrix, 0, 1); // matriz 4
    // print_dense_matrix(matrix[4]);
    
    matrix_transposed(matrix, 2);
    print_dense_matrix(matrix[3]);


    matrix_destroy(matrix);


    return 0;
}