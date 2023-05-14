#include "matrix.h"

//hyabak na holly

void printMenu(){

    printf("\n\nDigite o que deseja:\n\n");
    

}

int main(){
    int i, option = 0;
    Matrix_pt *matrix = NULL;

    printf("---------------\n Bem-vindo! :) \n---------------\n");
    printf("Uma matriz foi criada!\n");

    while(1){
        
        matrix = matrix_construct(matrix);

        printf("c? ");
        scanf("%d", &i);

        if( i == 0 )
        break;
    }

    assign_value_matrix(matrix); //ERRO
    // read_node_value_matrix(matrix); 
    // lalalu
  
    matrix_destroy(matrix);


    // while(1){
    //     //printMenu;
    //     scanf("\n%d");
    // }


    return 0;
}