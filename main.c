#include "headers/matrix.h"

//hyabak na holly
// gcc main.c -g -o main node.c position.c list.c matrix.c

void printMenu(){

    printf("\n\nDigite o que deseja:\n\n");
    

}

int main(){
    int i, option = 0;
    Matrix_pt *matrix = NULL;

    printf("---------------\n Bem-vindo! :) \n---------------\n");
    printf("Uma matriz foi criada!\n");

    matrix = matrix_construct(matrix, 2, 2);

    matrix = matrix_construct(matrix, 2, 2);

    assign_value_matrix(matrix, 0, 0, 0, 1); 
    print_dense_matrix(matrix, 0);

    assign_value_matrix(matrix, 1, 1, 1, 2); 
    print_dense_matrix(matrix, 1);

    read_node_value_matrix(matrix, 0, 0, 0); 
    read_node_value_matrix(matrix, 0, 1, 1); 
    

  
    destroy_matrix(matrix);


    return 0;
}