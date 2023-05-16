#include "headers/matrix.h"

int main(){
    Matrix **matrix = NULL;

    printf("---------------\n Bem-vindo! :) \n---------------\n");


    matrix = matrix_construct(matrix, 2, 2);
    matrix = matrix_construct(matrix, 2, 2);

    matrix = matrix_assign_value(matrix, 0, 0, 0, 1); 
    print_dense_matrix(matrix[0]);

    matrix = matrix_assign_value(matrix, 1, 1, 1, 2); 
    print_dense_matrix(matrix[1]);

    matrix_read_value(matrix[0], 0, 0, 0); 
    matrix_read_value(matrix[0], 0, 1, 1); 
    
    add_matrices(matrix, 0, 1);
    print_dense_matrix(matrix[2]);

    matrix_multiply_by_scalar(matrix[2], 3);
    print_dense_matrix(matrix[2]);


    matrix_destroy(matrix);


    return 0;
}