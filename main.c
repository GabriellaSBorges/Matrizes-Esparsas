#include "headers/matrix.h"

// comentar a saida!


int main(){
    int *qty_matrices = (int*) malloc( sizeof(int) );
    *qty_matrices = 0;

    printf("---------------\n Bem-vindo! :) \n---------------\n");


    printf("------------------ MATRIX 0 ------------------\n");

    /* Cria a matriz 0 e atribui valores a ela */
    Matrix *matrix_0 = matrix_construct(qty_matrices, 3, 3, 0); 

    matrix_assign_value(matrix_0, 2, 2, 0); 
    matrix_assign_value(matrix_0, 0, 0, 1); 
    matrix_assign_value(matrix_0, 1, 0, 0);
    matrix_assign_value(matrix_0, 1, 1, 1); 
    matrix_assign_value(matrix_0, 1, 2, 0); 
    matrix_assign_value(matrix_0, 0, 1, 2);
    matrix_assign_value(matrix_0, 0, 2, 3); 
    matrix_assign_value(matrix_0, 2, 0, 4); 
    matrix_assign_value(matrix_0, 2, 1, 3); 
    matrix_assign_value(matrix_0, 2, 2, 2); 
   
    print_sparse_matrix(matrix_0);
    print_dense_matrix(matrix_0);
    

    printf("------------------ MATRIX 1 ------------------\n");

    /* Cria a matriz 1 e atribui valores a ela */
    Matrix *matrix_1 = matrix_construct(qty_matrices, 3, 3, 0);

    matrix_assign_value(matrix_1, 0, 0, 3); 
    matrix_assign_value(matrix_1, 1, 2, 1); 
    matrix_assign_value(matrix_1, 2, 2, 0); 
    matrix_assign_value(matrix_1, 2, 1, 2); 
    matrix_assign_value(matrix_1, 0, 1, 0); 
    matrix_assign_value(matrix_1, 0, 2, 3); 
    matrix_assign_value(matrix_1, 1, 0, 0); 
    matrix_assign_value(matrix_1, 1, 1, 0); 
    matrix_assign_value(matrix_1, 2, 0, 2); 
   

    print_sparse_matrix(matrix_1);
    print_dense_matrix(matrix_1);


    /* OPERAÇÕES COM MATRIZES */
    matrix_read_value(matrix_0, 0, 1, 0); 
    matrix_read_value(matrix_1, 1, 2, 1); 


    
    /* Soma a matriz_0 com a matriz_1 */
    Matrix *matrix_2 = add_matrices(matrix_0, matrix_1, qty_matrices); 
    print_dense_matrix(matrix_2);

    /* Multiplica a matriz_0 por 2 */
    Matrix *matrix_3 = matrix_multiply_by_scalar(matrix_0, qty_matrices, 2); 
    print_dense_matrix(matrix_3);

    /* Multiplica a matriz_0 pela matriz_1 */
    Matrix *matrix_4 = matrices_multiply(matrix_0, matrix_1, qty_matrices); 
    print_dense_matrix(matrix_4);

    /* Multiplica a matriz_0 e a matriz_1 ponto a ponto */
    Matrix *matrix_5 = multiply_point_to_point(matrix_0, matrix_1, qty_matrices, 0); 
    print_dense_matrix(matrix_5);

    /* Troca as colunas 1 e 2 da matriz_5 */
    matrix_swap_columns(matrix_5, 1, 2); 
    print_dense_matrix(matrix_5);

    /* Troca as linhas 1 e 2 da matriz_5 */
    matrix_swap_lines(matrix_5, 1, 2); 
    print_dense_matrix(matrix_5);

    /* Retorna uma submatriz da matriz_5, sendo
    ponto inicial = linha 0 e coluna 0
    ponto final = linha 1 e coluna 2 */
    Matrix *matrix_6 = matrix_slice(matrix_5, qty_matrices, 0, 0, 1, 2, 0);
    print_dense_matrix(matrix_6);
    print_sparse_matrix(matrix_6);
    
    /* Retorna a matriz transposta da matriz 5 */
    Matrix *matrix_7 = matrix_transposed(matrix_5, qty_matrices); 
    print_dense_matrix(matrix_7);

    /* Salva a matriz 7 em um arquivo binário */
    save_binary_matrix(matrix_7, 7);
    matrix_destroy(matrix_7);

    /* Lê e inicializa uma matriz de um arquivo binário */
    Matrix *matrix_8 = read_binary_matrix(qty_matrices); 
    print_dense_matrix(matrix_8);


    /* CONVOLUÇÃO */

    printf("------------------ KERNEL ------------------\n");

    int *qty_kernels = (int*) malloc( sizeof(int) );
    *qty_kernels = 0;

    /* Cria um kernel 0 */
    Matrix *kernel_0 = matrix_construct(qty_kernels, 3, 3, 0); 

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

    /* Realiza a convolução a partir da matriz 8 e do kernel 0 */
    Matrix *matrix_9 = matrix_convolution(matrix_8, kernel_0, qty_matrices);
    print_dense_matrix(matrix_9);


    /* Libera toda a memória */
    matrix_destroy(matrix_0);
    matrix_destroy(matrix_1);
    matrix_destroy(matrix_2);
    matrix_destroy(matrix_3);
    matrix_destroy(matrix_4);
    matrix_destroy(matrix_5);
    matrix_destroy(matrix_6);
    matrix_destroy(matrix_8);
    matrix_destroy(matrix_9);

    matrix_destroy(kernel_0);

    free(qty_matrices);
    free(qty_kernels);

    return 0;
}