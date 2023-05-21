#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "list.h"

#define PATH_FILE "matrix.bin"

typedef struct Matrix Matrix;


/**
 * @brief Constroi uma matriz e atualiza a quantidade de matrizes
 * 
 * @param qty_matrices Ponteiro para a quantidade de matrizes construídas
 * @param qty_lines Quantidade de linhas da matriz construída
 * @param qty_columns Quantidade de colunas da matriz construída
 * @param hide_print Variável de apoio
 * Se for igual a 0, irá printar a confirmação de construção; se for igual a 1, irá bloquear o printf
 * 
 * @return Matrix* Ponteiro para a matriz criada
 */
Matrix *matrix_construct(int *qty_matrices, int qty_lines, int qty_columns, char hide_print);

/**
 * @brief Destrói a matriz e suas listas encadeadas
 * 
 * @param matrix Matriz que será destruída (memória liberada)
 */
void matrix_destroy(Matrix *matrix);

/**
 * @brief Atribui novo valor a uma célula da matriz
 * 
 * @param matrix Matriz que receberá o valor
 * @param l Linha do node em questão
 * @param c Coluna do node em questão
 * @param val Valor a ser atribuído
 */
void matrix_assign_value(Matrix *matrix, int l, int c, data_type val);

/**
 * @brief Lê o valor de uma célula da matriz, a partir da linha e da coluna
 * 
 * @param matrix Matriz desejada
 * @param index Índice da matriz na main (qtd de matrizes no momento em que foi construída)
 * @param l Linha desejada
 * @param c Coluna desejada
 */
void matrix_read_value(Matrix *matrix, int index, int l, int c);

/**
 * @brief Soma duas matrizes e retorna uma nova
 * @note Precisam ter o mesmo tamanho
 * 
 * @param matrix_1 Matriz número 1 que será somada
 * @param matrix_2 Matriz número 2 que será somada
 * @param qty_matrices Ponteiro para a quantidade de matrizes construídas pelo programa
 * @return Matrix* Nova matriz
 */
Matrix *add_matrices(Matrix *matrix_1, Matrix *matrix_2, int *qty_matrices);

/**
 * @brief Multiplica cada valor de uma matriz por um número escalar
 * 
 * @param matrix Matriz que será multiplicada
 * @param qty_matrices Ponteiro para a quantidade de matrizes construídas pelo programa
 * @param scalar Valor escalar que será usado
 * @return Matrix* Nova matriz
 */
Matrix *matrix_multiply_by_scalar(Matrix *matrix, int *qty_matrices, data_type scalar);

/**
 * @brief Multiplica duas matrizes
 * @note Para realizar a operação, o número de colunas da matriz_1 precisa igual ao número de linhas da matriz_2
 * 
 * @param matrix_1 Matriz 1 que será multiplicada (MxN)
 * @param matrix_2 Matriz 2 que será multiplicada (NxL)
 * @param qty_matrices Ponteiro para a quantidade de matrizes construídas pelo programa
 * @return Matrix* Matriz resultante (MxL)
 */
Matrix *matrices_multiply(Matrix *matrix_1, Matrix *matrix_2, int *qty_matrices);

/**
 * @brief Multiplica duas matrizes ponto a ponto
 * @note Precisam ter o mesmo tamanho
 * 
 * @param matrix_1 Matriz 1 que será multiplicada 
 * @param matrix_2 Matriz 2 que será multiplicada
 * @param qty_matrices Ponteiro para a quantidade de matrizes construídas pelo programa
 * @param hide_print Variável de apoio
 * Se for igual a 0, irá printar a confirmação de construção; se for igual a 1, irá bloquear o printf
 * 
 * @return Matrix* Nova matriz
 */
Matrix *multiply_point_to_point(Matrix *matrix_1, Matrix *matrix_2, int *qty_matrices, char hide_print);

/**
 * @brief Troca duas colunas de uma matriz
 * 
 * @param matrix Matriz desejada
 * @param index_1 Índice da coluna 1 que será trocada
 * @param index_2 Índice da coluna 2 que será trocada
 * @note A operação é in-place, não cria uma nova matriz
 */
void matrix_swap_columns(Matrix *matrix, int index_1, int index_2);

/**
 * @brief Troca duas linhas de uma matriz
 * 
 * @param matrix Matriz desejada
 * @param index_1 Índice da linha 1 que será trocada
 * @param index_2 Índice da linha 2 que será trocada
 * @note A operação é in-place, não cria uma nova matriz
 */
void matrix_swap_lines(Matrix *matrix, int index_1, int index_2);

/**
 * @brief Cria e retorna uma submatriz a partir de uma matriz base e dois pontos: ínicio e fim
 * 
 * @param matrix Matriz base
 * @param qty_matrices Ponteiro para a quantidade de matrizes construídas pelo programa
 * @param start_line Linha do ponto inicial
 * @param start_column Coluna do ponto inicial
 * @param end_line Linha do ponto final
 * @param end_column Coluna do ponto final
 * @param hide_print Variável de apoio
 * Se for igual a 0, irá printar a confirmação de construção; se for igual a 1, irá bloquear o printf
 * 
 * @return Matrix* Submatriz
 */
Matrix *matrix_slice(Matrix *matrix, int *qty_matrices, int start_line, int start_column, int end_line, int end_column, char hide_print);

/**
 * @brief Cria uma nova matriz, transposta à matriz base
 * 
 * @param matrix Matriz base
 * @param qty_matrices Ponteiro para a quantidade de matrizes construídas pelo programa
 * @return Matrix* Nova matriz
 * @note A nova matriz terá:
 * qtd de linhas = qtd de colunas da matriz base
 * qtd de colunas = qtd de linhas da matriz base
 */
Matrix *matrix_transposed(Matrix *matrix, int *qty_matrices);

/**
 * @brief Realiza a convolução de uma matriz por um kernel e retorna a matriz resultante
 * 
 * @param matrix Matriz base
 * @param kernel Matriz usada no cálculo da convolução
 * @param qty_matrices Ponteiro para a quantidade de matrizes construídas pelo programa
 * @return Matrix* Nova matriz
 */
Matrix *matrix_convolution(Matrix *matrix, Matrix *kernel, int *qty_matrices);

/**
 * @brief Soma todos os valores presentes em uma matriz
 * 
 * @param matrix Matriz desejada
 * @return data_type Resultado da soma
 */
data_type add_all_values(Matrix *matrix);

/**
 * @brief Imprime uma matriz de forma densa (apresnetando os zeros)
 * 
 * @param matrix Matriz desejada
 */
void print_dense_matrix(Matrix *matrix);

/**
 * @brief Imprime uma matriz de forma esparsa (sem os zeros)
 * 
 * @param matrix Matriz desejada 
 */
void print_sparse_matrix(Matrix *matrix);

/**
 * @brief Salva uma matriz em um arquivo binário
 * 
 * @param matrix Matriz desejada
 */
void save_binary_matrix(Matrix *matrix);

/**
 * @brief Lê uma matriz de um arquivo binário e aloca memória para ela
 * 
 * @param qty_matrices Ponteiro para a quantidade de matrizes construídas pelo programa
 * @return Matrix* Matriz lida
 */
Matrix *read_binary_matrix(int *qty_matrices);


#endif