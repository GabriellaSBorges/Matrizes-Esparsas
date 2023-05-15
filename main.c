#include "headers/matrix.h"

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
        
        matrix = create_matrix(matrix);
        assign_value_matrix(matrix); 
        print_dense_matrix(matrix);

        printf("c? ");
        scanf("%d", &i);

        if( i == 0 )
        break;
    }

    add_matrices(matrix); 

    while(1){ 
        //read_node_value_matrix(matrix); 

        print_dense_matrix(matrix);

        printf("c? ");
        scanf("%d", &i);

        if( i == 0 )
        break;
    }
    

  
    destroy_matrix(matrix);




    return 0;
}