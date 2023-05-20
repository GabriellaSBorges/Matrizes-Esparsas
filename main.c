#include "headers/matrix.h"

int main(){
    int *qty_matrices = (int*) malloc( sizeof(int) );
    *qty_matrices = 0;

    printf("---------------\n Bem-vindo! :) \n---------------\n");


    Matrix *matrix_0 = matrix_construct(qty_matrices, 3, 3); 

    matrix_assign_value(matrix_0, 0, 0, 1); 
    matrix_assign_value(matrix_0, 2, 1, 1); 
    matrix_assign_value(matrix_0, 2, 2, 2); 
    matrix_assign_value(matrix_0, 0, 1, 2); 
    
    matrix_assign_value(matrix_0, 1, 1, 1); 
    matrix_assign_value(matrix_0, 1, 2, 1); 
    matrix_assign_value(matrix_0, 2, 0, 2); 
    matrix_assign_value(matrix_0, 0, 2, 3); 
    matrix_assign_value(matrix_0, 1, 0, 4); 
  
    // print_sparse_matrix(matrix_0);
    print_dense_matrix(matrix_0);


    Matrix *matrix_1 = matrix_construct(qty_matrices, 3, 3);

    matrix_assign_value(matrix_1, 0, 0, 2); 
    matrix_assign_value(matrix_1, 0, 1, 3); 
    matrix_assign_value(matrix_1, 1, 0, 1); 
    matrix_assign_value(matrix_1, 1, 1, 3); 
    matrix_assign_value(matrix_1, 0, 2, 1); 
    matrix_assign_value(matrix_1, 1, 2, 1); 
    matrix_assign_value(matrix_1, 1, 1, 2); 
    matrix_assign_value(matrix_1, 0, 2, 1); 
    matrix_assign_value(matrix_1, 2, 2, 1); 

    // print_sparse_matrix(matrix_1);
    print_dense_matrix(matrix_1);


    matrix_read_value(matrix_0, 0, 0, 0); 
    matrix_read_value(matrix_0, 0, 1, 1); 
    
    Matrix *matrix_2 = add_matrices(matrix_0, matrix_1, qty_matrices); 
    print_dense_matrix(matrix_2);

    Matrix *matrix_3 = matrix_multiply_by_scalar(matrix_2, qty_matrices, 2); 
    print_dense_matrix(matrix_3);

    Matrix *matrix_4 = matrices_multiply(matrix_0, matrix_1, qty_matrices); 
    print_dense_matrix(matrix_4);

    // multiply_point_to_point(matrix, 0, 1); // matriz 4
    // print_dense_matrix(matrix[4]);

    // matrix_swap_columns(matrix[0], 1, 2, 'c'); 
    // print_dense_matrix(matrix[0]);

    
    // matrix_transposed(matrix, 2); //matriz 3
    // print_dense_matrix(matrix[3]);

    // save_binary_matrix(matrix[2]);
    // read_binary_matrix(matrix); // matriz 3
    // print_dense_matrix(matrix[3]);

    // Position *start = NULL, *end = NULL;
    // start = position_construct(start, 0, 0); 
    // end = position_construct(end, 1, 1); 

    // matrix_slice(matrix, 0, 0, 0, 1, 1);
    // print_dense_matrix(matrix[2]);

    int *qty_kernels = (int*) malloc( sizeof(int) );
    *qty_kernels = 0;

    Matrix *kernel_0 = matrix_construct(qty_kernels, 3, 3); // kernel 0

    matrix_assign_value(kernel_0, 0, 0, 1); 
    matrix_assign_value(kernel_0, 0, 1, 0); 
    matrix_assign_value(kernel_0, 0, 2, 1); 
    matrix_assign_value(kernel_0, 1, 0, 0); 
    matrix_assign_value(kernel_0, 1, 1, 1); 
    matrix_assign_value(kernel_0, 1, 2, 0); 
    matrix_assign_value(kernel_0, 2, 0, 1); 
    matrix_assign_value(kernel_0, 2, 1, 0); 
    matrix_assign_value(kernel_0, 2, 2, 1); 

    print_dense_matrix(kernel_0);

    // matrix_convolution(matrix, 0, kernel, 0);

    matrix_destroy(matrix_0);
    matrix_destroy(matrix_1);
    matrix_destroy(matrix_2);
    matrix_destroy(matrix_3);
    matrix_destroy(matrix_4);
    matrix_destroy(kernel_0);
    free(qty_matrices);
    free(qty_kernels);

    return 0;
}