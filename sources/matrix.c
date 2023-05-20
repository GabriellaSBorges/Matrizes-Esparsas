#include "../headers/matrix.h"

struct Matrix{
    List **lines;
    List **columns;
    int number_lines;
    int number_columns;
};


Matrix *matrix_construct(int *qty_matrices, int qty_lines, int qty_columns){

    Matrix *matrix = (Matrix*) malloc( sizeof(Matrix) );

    matrix->number_lines = qty_lines;
    matrix->number_columns = qty_columns;
    (*qty_matrices)++;

    if( matrix != NULL ){
        printf("\n|Matrix-%d was constructed!\n\n", (*qty_matrices)-1);

    } else {
        printf("ERROR: failure to build the matrix.\n\n");
        exit(1);
    }

    matrix->lines = list_construct( matrix->lines, matrix->number_lines );
    matrix->columns = list_construct( matrix->lines, matrix->number_columns );

    return matrix;
}

void matrix_destroy(Matrix *matrix){

    list_destroy(matrix->lines, matrix->number_lines, 'l');
    list_destroy(matrix->columns, matrix->number_columns, 'c');
    
    free(matrix);
}

void matrix_assign_value(Matrix *matrix, int l, int c, data_type val){

    Node *node = find_node_row(matrix->lines[l], c, 'a', 'l', 'c');

    if( node && val != 0 )
        node_assign_value(node, val);

    else if( node && val == 0 )
        list_decrement(matrix->lines[l], matrix->columns[c], l, c);

    else if( !node && val != 0 ){
        list_increment(matrix->lines[l], matrix->columns[c], l, c, val);

    }
}

void matrix_read_value(Matrix *matrix, int index, int l, int c){

    Node *n = find_node_row(matrix->lines[l], c, 'a', 'l', 'c');
    data_type *val = node_return_value(n);

    if( n == NULL )
        printf("Value of the node [%d,%d] in matrix '%d': %f\n\n", l, c, index, 0.0);
    else
        printf("Value of the node [%d,%d] in matrix '%d': %f\n\n", l, c, index, *val);
}

Matrix *add_matrices(Matrix *matrix_1, Matrix *matrix_2, int *qty_matrices){
    data_type new_value = 0;
    int c = 0;

    printf("\n|ADD MATRICES|\n");

    Matrix *new_matrix = matrix_construct(qty_matrices, matrix_1->number_lines, matrix_1->number_columns);

    for( int l = 0; l < matrix_1->number_lines; l++ ){
        ListIterator *li_1 = list_front_iterator(matrix_1->lines[l]);
        ListIterator *li_2 = list_front_iterator(matrix_2->lines[l]);

        while( !list_iterator_is_over(li_1) || !list_iterator_is_over(li_2) ){

                if( !list_iterator_is_over(li_1) && !list_iterator_is_over(li_2) &&
                    list_iterator_return_place(li_1, 'c') == list_iterator_return_place(li_2, 'c') ){
                    c = list_iterator_return_place(li_1, 'c');

                    new_value = *list_iterator_next(li_1, 'l') + *list_iterator_next(li_2, 'l');
                    list_increment(new_matrix->lines[l], new_matrix->columns[c], l, c, new_value);

                } else if( !list_iterator_is_over(li_1) && (list_iterator_is_over(li_2)  ||
                list_iterator_return_place(li_1, 'c') < list_iterator_return_place(li_2, 'c')) ){
                    c = list_iterator_return_place(li_1, 'c');
                    new_value = *list_iterator_next(li_1, 'l');

                    list_increment(new_matrix->lines[l], new_matrix->columns[c], l, c, new_value);

                } else if ( list_iterator_is_over(li_1) && (!list_iterator_is_over(li_2) ||
                list_iterator_return_place(li_1, 'c') > list_iterator_return_place(li_2, 'c')) ){
                    c = list_iterator_return_place(li_2, 'c');
                    new_value = *list_iterator_next(li_2, 'l');

                    list_increment(new_matrix->lines[l], new_matrix->columns[c], l, c, new_value);
                }     
        }  
        free(li_1);
        free(li_2);            
    }
    return new_matrix;
}

Matrix *matrix_multiply_by_scalar(Matrix *matrix, int *qty_matrices, data_type scalar){
    ListIterator *li = NULL;

    printf("\n|MULTIPLY BY SCALAR|\n");

    Matrix *new_matrix = matrix_construct(qty_matrices, matrix->number_lines, matrix->number_columns);

    for( int l = 0; l < matrix->number_lines; l++ ){
        li = list_front_iterator(matrix->lines[l]);

        while( !list_iterator_is_over(li) ){
            int c = list_iterator_return_place(li, 'c');
            data_type val = *list_iterator_next(li, 'l');

            list_increment(new_matrix->lines[l], new_matrix->columns[c], l, c, val*scalar);
        }
        free(li);
    }
    return new_matrix;
}

//mudar
Matrix *matrices_multiply(Matrix *matrix_1, Matrix *matrix_2, int *qty_matrices){
    data_type value_1 = 0, value_2 = 0, new_value = 0;

    printf("\n|MULTIPLY MATRICES|\n");

    Matrix *new_matrix = matrix_construct(qty_matrices, matrix_1->number_lines, matrix_2->number_columns);

    for( int l = 0; l < matrix_1->number_lines; l++ ){ 
        for( int c = 0; c < matrix_2->number_columns; c++ ){
            ListIterator *li_1 = list_front_iterator(matrix_1->lines[l]);
            ListIterator *li_2 = list_front_iterator(matrix_2->columns[c]);
            new_value = 0;
            

            while( !list_iterator_is_over(li_1) && !list_iterator_is_over(li_2) ){

                if( list_iterator_return_place(li_1, 'c') == list_iterator_return_place(li_2, 'l') ){

                    value_1 = *list_iterator_next(li_1, 'l');
                    value_2 = *list_iterator_next(li_2, 'c');
                    new_value += value_1 * value_2;

                } else if( list_iterator_return_place(li_1, 'c') < list_iterator_return_place(li_2, 'l') ){
                    list_iterator_next(li_1, 'l');

                } else if ( list_iterator_return_place(li_1, 'c') > list_iterator_return_place(li_2, 'l') ){
                    list_iterator_next(li_2, 'c');
                }     
            }  

            list_increment(new_matrix->lines[l], new_matrix->columns[c], l, c, new_value);
            
            free(li_1);
            free(li_2);
        }                     
    }
      
    return new_matrix;
}

Matrix *multiply_point_to_point(Matrix *matrix_1, Matrix *matrix_2, int *qty_matrices){

    printf("\n|MULTIPLY POINT TO POINT|\n");

    Matrix *new_matrix = matrix_construct(qty_matrices, matrix_1->number_lines, matrix_2->number_columns);


    for( int l = 0; l < matrix_1->number_lines; l++ ){ 
        ListIterator *li_1 = list_front_iterator(matrix_1->lines[l]);
        ListIterator *li_2 = list_front_iterator(matrix_2->lines[l]);

        while( !list_iterator_is_over(li_1) && !list_iterator_is_over(li_2) ){

            if( list_iterator_return_place(li_1, 'c') == list_iterator_return_place(li_2, 'c') ){
                int c = list_iterator_return_place(li_1, 'c');

                data_type new_value = *list_iterator_next(li_1, 'l') * *list_iterator_next(li_2, 'l');

                list_increment(new_matrix->lines[l], new_matrix->columns[c], l, c, new_value);


            } else if( list_iterator_return_place(li_1, 'c') < list_iterator_return_place(li_2, 'c') ){
                list_iterator_next(li_1, 'l');


            } else if ( list_iterator_return_place(li_1, 'c') > list_iterator_return_place(li_2, 'c') ){
                list_iterator_next(li_2, 'l');
            }     
        }  
        free(li_1);
        free(li_2);                                 
    }     
    
    return new_matrix;
}

void matrix_swap_columns(Matrix *matrix, int index_1, int index_2, char list_type){ 

    printf("\n|SWAP COLUMNS|\n");
    
    for( int l = 0; l < matrix->number_lines; l++ ){
        ListIterator *li = list_front_iterator(matrix->lines[l]);
        data_type *val_1 = NULL, *val_2 = NULL, aux;
        int swap_confirm = 0;

        while( !list_iterator_is_over(li) ){
            
            if( list_iterator_return_place(li, list_type) == index_1 ){
                val_1 = list_iterator_next(li, 'l');

            } else if( list_iterator_return_place(li, list_type) == index_2 && val_1 != NULL ){
                val_2 = list_iterator_next(li, 'l');
                
                aux = *val_2;
                *val_2 = *val_1;
                *val_1 = aux;

                swap_confirm++;
                break;

            } else if( list_iterator_return_place(li, list_type) == index_2 && val_1 == NULL ){
                val_2 = list_iterator_next(li, 'l');

                list_increment(matrix->lines[l], matrix->columns[index_1], l, index_1, *val_2);
                list_decrement(matrix->lines[l], matrix->columns[index_2], l, index_2);
                
                swap_confirm++;
                break;

            } else if( list_iterator_return_place(li, list_type) > index_2 && val_1 != NULL ){

                list_increment(matrix->lines[l], matrix->columns[index_2], l, index_2, *val_1);
                list_decrement(matrix->lines[l], matrix->columns[index_1], l, index_1);

                swap_confirm++;
                break;
                
            } else {
                list_iterator_next(li, 'l');
          }          
        }

        /* se a lista acabou antes de chegar ao índice 2, realiza o swap */
        if( val_1 != NULL && !swap_confirm ){
            list_increment(matrix->lines[index_2], matrix->columns[l], l, index_2, *val_1);
            list_decrement(matrix->lines[index_1], matrix->columns[l], l, index_1);
        }

        free(li);
    }


}

void matrix_swap_lines(Matrix *matrix, int index_1, int index_2, char list_type){ 

    printf("\n|SWAP LINES|\n");
    
    for( int c = 0; c < matrix->number_columns; c++ ){
        ListIterator *li = list_front_iterator(matrix->columns[c]);
        data_type *val_1 = NULL, *val_2 = NULL, aux;
        int swap_confirm = 0;

        while( !list_iterator_is_over(li) ){
            
            if( list_iterator_return_place(li, list_type) == index_1 ){
                val_1 = list_iterator_next(li, 'c');

            } else if( list_iterator_return_place(li, list_type) == index_2 && val_1 != NULL ){
                val_2 = list_iterator_next(li, 'c');
                
                aux = *val_2;
                *val_2 = *val_1;
                *val_1 = aux;

                swap_confirm++;
                break;

            } else if( list_iterator_return_place(li, list_type) == index_2 && val_1 == NULL ){
                val_2 = list_iterator_next(li, 'c');

                list_increment(matrix->lines[index_1], matrix->columns[c], index_1, c, *val_2);
                list_decrement(matrix->lines[index_2], matrix->columns[c], index_2, c);

                swap_confirm++;
                break;

            } else if( list_iterator_return_place(li, list_type) > index_2 && val_1 != NULL ){

                list_increment(matrix->lines[index_2], matrix->columns[c], index_2, c, *val_1);
                list_decrement(matrix->lines[index_1], matrix->columns[c], index_1, c);

                swap_confirm++;
                break;
                
            } else {
                list_iterator_next(li, 'c');
            }          
        }

        /* se a lista acabou antes de chegar ao índice 2, realiza o swap */
        if( val_1 != NULL && !swap_confirm ){
            list_increment(matrix->lines[index_2], matrix->columns[c], index_2, c, *val_1);
            list_decrement(matrix->lines[index_1], matrix->columns[c], index_1, c);
        }

        free(li);
    }

}

Matrix *matrix_slice(Matrix *matrix, int *qty_matrices, int start_line, int start_column, int end_line, int end_column){

    printf("\n|MATRIX SLICE|\n");

    int qty_lines = end_line - start_line + 1;
    int qty_columns = end_column - start_column + 1;

    Matrix *new_matrix = matrix_construct(qty_matrices, qty_lines, qty_columns);

    // printf("Q %d %d %d", qty_lines, qty_columns, new_index);

    for( int l = start_line; l <= end_line; l++ ){

        if( l >= 0 && l < matrix->number_lines ){
            ListIterator *li = list_front_iterator(matrix->lines[l]);

            while( !list_iterator_is_over(li) ){
                int c = list_iterator_return_place(li, 'c');
                data_type val = *list_iterator_next(li, 'l');

                if( c >= start_column && c <= end_column ){
                    int new_line = l - start_line;
                    int new_column = c - start_column;

                    list_increment(new_matrix->lines[new_line], new_matrix->columns[new_column], new_line, new_column, val);
                }            
            }
            free(li);   
        }              
    }

    return new_matrix;
}

Matrix *matrix_transposed(Matrix *matrix, int *qty_matrices){

    printf("\n|TRANSPOSED MATRIX|\n");

    int qty_lines = matrix->number_columns;
    int qty_columns = matrix->number_lines;

    Matrix *new_matrix = matrix_construct(qty_matrices, qty_lines, qty_columns);

    for( int l = 0; l < matrix->number_lines; l++ ){
        ListIterator *li = list_front_iterator(matrix->lines[l]);

        while( !list_iterator_is_over(li) ){
            int c = list_iterator_return_place(li, 'c');
            data_type val = *list_iterator_next(li, 'l');
            
            list_increment(new_matrix->lines[c], new_matrix->columns[l], c, l, val);
        }
        free(li);
    }

    return new_matrix;
}

void matrix_convolution(Matrix *matrix, Matrix *kernel, int *qty_matrices){
    Matrix *support_1 = NULL, *support_2 = NULL;
    int *qty_supports = (int*) malloc( sizeof(int) );

    /* Calcula a quantidade de linhas da célula central até a borda */
    int edge_kernel = kernel->number_lines/2;


    for( int l = 0; l < matrix->number_lines; l++ ){
        for( int c = 0; c < matrix->number_columns; c++ ){
            (*qty_supports) = 0;

            support_1 = matrix_slice(matrix, qty_matrices, l-edge_kernel, c-edge_kernel, l+edge_kernel, c+edge_kernel);
            print_dense_matrix(support_1);

            support_2 = multiply_point_to_point(support_1, kernel, qty_supports);


            matrix_destroy(support_1);          
            matrix_destroy(support_2);          
        }
    }


    free(qty_supports);
}







void print_dense_matrix(Matrix *matrix){
    ListIterator *li = NULL;
    data_type value = 0;

    printf(":dense matrix:\n");

    for( int l = 0; l < matrix->number_lines; l++ ){
        li = list_front_iterator(matrix->lines[l]);

        for( int c = 0; c < matrix->number_columns; c++ ){

            if( !list_iterator_is_over(li) && list_iterator_return_place(li, 'c') == c )
                value = *list_iterator_next(li, 'l');
            else 
                value = 0;
 
            printf("%.0f ", value);
        }
        free(li);
        printf("\n");
    }
    printf("\n");

    // 
}

void print_sparse_matrix(Matrix *matrix){
    ListIterator *li = NULL;
    data_type value = 0;
    int c = 0;

    printf("\n:sparse matrix:\n");

    for( int l = 0; l < matrix->number_lines; l++ ){
        li = list_front_iterator(matrix->lines[l]);

        while( !list_iterator_is_over(li) ){
            c = list_iterator_return_place(li, 'c');
            value = *list_iterator_next(li, 'l');

            printf("%.0f [%dx%d]  ", value, l, c);
        }            
        free(li);
        printf("\n");
    }
    printf("\n");
}

void save_binary_matrix(Matrix *matrix){
    char path[11] = PATH_FILE;
    FILE *arq = fopen(path, "wb");

    printf("\n|SAVE MATRIX|\n");

    if( !arq ){
        printf("ERROR: couldn't open the file!\n");
        exit(1);
    }
    printf("File open!");    

    fwrite( &matrix->number_lines, sizeof(int), 1, arq);
    fwrite( &matrix->number_columns, sizeof(int), 1, arq);

    for( int i = 0; i < matrix->number_lines; i++ )
        save_binary_list(arq, matrix->lines[i]);
    
    printf("\nThe matrix was saved in the file '%s'!\n", PATH_FILE);    

    fclose(arq);
}

Matrix *read_binary_matrix(int *qty_matrices){
    char path[11] = PATH_FILE;
    FILE *arq = fopen(path, "rb");

    printf("\n|READ MATRIX|\n");

    if( !arq ){
        printf("ERROR: couldn't open the file!\n");
        exit(1);
    }
    printf("File open!");  


    int qty_lines = 0, qty_columns = 0;

    fread( &qty_lines, sizeof(int), 1, arq);
    fread( &qty_columns, sizeof(int), 1, arq);

    Matrix *new_matrix = matrix_construct(qty_matrices, qty_lines, qty_columns);


    for( int i = 0; i < new_matrix->number_lines; i++ )
        read_binary_list(arq, new_matrix->lines, new_matrix->columns, i);

    fclose(arq);

    return new_matrix;
}
