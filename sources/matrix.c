#include "../headers/matrix.h"

struct Matrix{
    List_pt *lines;
    List_pt *columns;
    int number_lines;
    int number_columns;
    int qty_allocated;
    int quantity;
};



Matrix **matrix_construct(Matrix **matrix, int qty_lines, int qty_columns){
    int qty = 0;

    if( matrix != NULL )
        qty = matrix[0]->quantity;

    matrix = alloc_and_realloc_matrix(matrix, qty); 
    verify_matrix(matrix);
    matrix = initialize_matrix(matrix, qty_lines, qty_columns);

    int index = matrix[0]->quantity-1;

    matrix[index]->lines = list_construct( matrix[index]->lines, matrix[index]->number_lines );
    matrix[index]->columns = list_construct( matrix[index]->lines, matrix[index]->number_columns );

    return matrix;
}

Matrix **alloc_and_realloc_matrix(Matrix **matrix, int qty_matrices){
    int i = 0, inicial_qty = 0;

    if( !qty_matrices ){
        matrix = (Matrix**) malloc( QTY_ALLOC_INITIALLY * sizeof(Matrix*) ); 

        for( i = inicial_qty; i < QTY_ALLOC_INITIALLY; i++ ){
            matrix[i] = (Matrix*) malloc( sizeof(Matrix) );
        }

        matrix[0]->qty_allocated = QTY_ALLOC_INITIALLY;
        matrix[0]->quantity = 0;

    } else if( qty_matrices == matrix[0]->qty_allocated ) {
        inicial_qty = matrix[0]->qty_allocated;
        matrix[0]->qty_allocated *= 2;

        matrix = realloc( matrix, matrix[0]->qty_allocated * sizeof(Matrix*) );

        for( i = inicial_qty; i < matrix[0]->qty_allocated; i++ ){
            matrix[i] = (Matrix*) malloc( sizeof(Matrix) );
        }
    }

    return matrix;
}

Matrix **initialize_matrix(Matrix **matrix, int l, int c){
    
    matrix[matrix[0]->quantity]->number_lines = l;
    matrix[matrix[0]->quantity]->number_columns = c;
    matrix[0]->quantity++;

    return matrix;
}

void verify_matrix(Matrix **matrix){

    if( matrix != NULL ){
        printf("The matrix-%d was constructed!\n\n", matrix[0]->quantity);

    } else {
        printf("ERROR: failure to build the matrix.\n\n");
        exit(1);
    }
}

void matrix_destroy(Matrix **matrix){
    int qty_alloc = matrix[0]->qty_allocated;
    int qty_matrices = matrix[0]->quantity;

    for( int i = 0; i < qty_alloc; i++ ){

        if( i < qty_matrices ){
            list_destroy(matrix[i]->lines, matrix[i]->number_lines, 'l');
            list_destroy(matrix[i]->columns, matrix[i]->number_columns, 'c');
        }
       
        free(matrix[i]);
    }
    free(matrix);
}

void matrix_assign_value(Matrix *matrix, int l, int c, data_type val){

    int position_occupied = verify_position_occupied(matrix->lines[l], c, 'c');

    if( position_occupied && val != 0 )
        list_assign_value(matrix->lines[l], c, val, 'c');

    else if( position_occupied && val == 0 )
        list_decrement(matrix->lines[l], matrix->columns[c], l, c);

    else if( !position_occupied && val != 0 ){
        list_increment(matrix->lines[l], matrix->columns[c], l, c, val);

    }
}

void matrix_read_value(Matrix *matrix, int index, int l, int c){

    Node_pt n = find_node_row(matrix->lines[l], c, 'a', 'l', 'c');
    data_type *val = node_return_value(n);

    if( n == NULL )
        printf("Value of the node [%d,%d] in matrix '%d': %f\n\n", l, c, index, 0.0);
    else
        printf("Value of the node [%d,%d] in matrix '%d': %f\n\n", l, c, index, *val);
}

void add_matrices(Matrix **matrix, int index_1, int index_2){
    data_type value_1 = 0, value_2 = 0, new_value = 0;
    int c = 0;

    if( matrix[index_1]->number_lines != matrix[index_2]->number_lines || 
    matrix[index_1]->number_columns != matrix[index_2]->number_columns ){
        printf("Matrices of different sizes cannot be added!\n\n");

    } else {
        matrix = matrix_construct(matrix, matrix[index_1]->number_lines, matrix[index_1]->number_columns);
        int new_index = matrix[0]->quantity-1;

        for( int l = 0; l < matrix[index_1]->number_lines; l++ ){
            ListIterator *li_1 = list_front_iterator(matrix[index_1]->lines[l]);
            ListIterator *li_2 = list_front_iterator(matrix[index_2]->lines[l]);

            while( !list_iterator_is_over(li_1) || !list_iterator_is_over(li_2) ){

                    if( !list_iterator_is_over(li_1) && !list_iterator_is_over(li_2) &&
                     list_iterator_return_place(li_1, 'c') == list_iterator_return_place(li_2, 'c') ){
                        c = list_iterator_return_place(li_1, 'c');

                        value_1 = *list_iterator_next(li_1, 'l');
                        value_2 = *list_iterator_next(li_2, 'l');

                        new_value = value_1 + value_2;
                        list_increment(matrix[new_index]->lines[l], matrix[new_index]->columns[c], l, c, new_value);

                    } else if( !list_iterator_is_over(li_1) && (list_iterator_is_over(li_2)  ||
                    list_iterator_return_place(li_1, 'c') < list_iterator_return_place(li_2, 'c')) ){
                        c = list_iterator_return_place(li_1, 'c');
                        new_value = *list_iterator_next(li_1, 'l');

                        list_increment(matrix[new_index]->lines[l], matrix[new_index]->columns[c], l, c, new_value);

                    } else if ( list_iterator_is_over(li_1) && (!list_iterator_is_over(li_2) ||
                    list_iterator_return_place(li_1, 'c') > list_iterator_return_place(li_2, 'c')) ){
                        c = list_iterator_return_place(li_2, 'c');
                        new_value = *list_iterator_next(li_2, 'l');

                        list_increment(matrix[new_index]->lines[l], matrix[new_index]->columns[c], l, c, new_value);
                    }     
            }  
            free(li_1);
            free(li_2);            
        }
      
    }

}

void matrix_multiply_by_scalar(Matrix *matrix, data_type scalar){
    ListIterator *li = NULL;
    data_type *val;

    for( int l = 0; l < matrix->number_lines; l++ ){
        li = list_front_iterator(matrix->lines[l]);

        while( !list_iterator_is_over(li) ){
            val = list_iterator_next(li, 'l');
            (*val) *= scalar;
        }
        free(li);
    }

}

void matrices_multiply(Matrix **matrix, int index_1, int index_2){
    data_type value_1 = 0, value_2 = 0, new_value = 0;

    if( matrix[index_1]->number_columns != matrix[index_2]->number_lines ){
        printf("These matrices cannot be multiplied!\n\n");

    } else {
        matrix = matrix_construct(matrix, matrix[index_1]->number_lines, matrix[index_1]->number_columns);
        int new_index = matrix[0]->quantity-1;

        for( int l = 0; l < matrix[index_1]->number_lines; l++ ){ 
            for( int c = 0; c < matrix[index_2]->number_columns; c++ ){
                ListIterator *li_1 = list_front_iterator(matrix[index_1]->lines[l]);
                ListIterator *li_2 = list_front_iterator(matrix[index_2]->columns[c]);
                new_value = 0;
                

                while( !list_iterator_is_over(li_1) || !list_iterator_is_over(li_2) ){

                    if( !list_iterator_is_over(li_1) && !list_iterator_is_over(li_2) &&
                     list_iterator_return_place(li_1, 'c') == list_iterator_return_place(li_2, 'l') ){

                        value_1 = *list_iterator_next(li_1, 'l');
                        value_2 = *list_iterator_next(li_2, 'c');
                        new_value += value_1 * value_2;

                    } else if( !list_iterator_is_over(li_1) && (list_iterator_is_over(li_2)  ||
                    list_iterator_return_place(li_1, 'c') < list_iterator_return_place(li_2, 'l')) ){
                        list_iterator_next(li_1, 'l');

                    } else if ( list_iterator_is_over(li_1) && (!list_iterator_is_over(li_2) ||
                    list_iterator_return_place(li_1, 'c') > list_iterator_return_place(li_2, 'l')) ){
                        list_iterator_next(li_2, 'c');
                    }     
                }  

                list_increment(matrix[new_index]->lines[l], matrix[new_index]->columns[c], l, c, new_value);
                
                free(li_1);
                free(li_2);
            }                     
        }
      
    }
}

void multiply_point_to_point(Matrix **matrix, int index_1, int index_2){
    data_type value_1 = 0, value_2 = 0, new_value = 0;

    if( matrix[index_1]->number_lines != matrix[index_2]->number_lines || 
    matrix[index_1]->number_columns != matrix[index_2]->number_columns ){
        printf("These matrices cannot be multiplied!\n\n");

    } else {
        matrix = matrix_construct(matrix, matrix[index_1]->number_lines, matrix[index_1]->number_columns);
        int new_index = matrix[0]->quantity-1;

        for( int l = 0; l < matrix[index_1]->number_lines; l++ ){ 
            ListIterator *li_1 = list_front_iterator(matrix[index_1]->lines[l]);
            ListIterator *li_2 = list_front_iterator(matrix[index_2]->lines[l]);

            while( !list_iterator_is_over(li_1) || !list_iterator_is_over(li_2) ){

                if( !list_iterator_is_over(li_1) && !list_iterator_is_over(li_2) &&
                    list_iterator_return_place(li_1, 'c') == list_iterator_return_place(li_2, 'c') ){
                    int c = list_iterator_return_place(li_1, 'c');

                    value_1 = *list_iterator_next(li_1, 'l');
                    value_2 = *list_iterator_next(li_2, 'l');
                    new_value = value_1*value_2;

                    list_increment(matrix[new_index]->lines[l], matrix[new_index]->columns[c], l, c, new_value);

                } else if( !list_iterator_is_over(li_1) && (list_iterator_is_over(li_2)  ||
                list_iterator_return_place(li_1, 'c') < list_iterator_return_place(li_2, 'c')) ){
                    list_iterator_next(li_1, 'l');

                } else if ( list_iterator_is_over(li_1) && (!list_iterator_is_over(li_2) ||
                list_iterator_return_place(li_1, 'c') > list_iterator_return_place(li_2, 'c')) ){
                    list_iterator_next(li_2, 'l');
                }     
            }  
            free(li_1);
            free(li_2);                                 
        }     
    }
}

void matrix_swap_columns(Matrix *matrix, int index_1, int index_2, char list_type){ 
    
    for( int l = 0; l < matrix->number_lines; l++ ){
        ListIterator *li = list_front_iterator(matrix->lines[l]);
        data_type *val_1 = NULL, *val_2 = NULL, aux;


        while( !list_iterator_is_over(li) ){
            
            if( list_iterator_return_place(li, list_type) == index_1 ){
                val_1 = list_iterator_next(li, 'l');

            } else if( list_iterator_return_place(li, list_type) == index_2 && val_1 != NULL ){
                val_2 = list_iterator_next(li, 'l');
                
                aux = *val_2;
                *val_2 = *val_1;
                *val_1 = aux;

                break;

            } else if( list_iterator_return_place(li, list_type) == index_2 && val_1 == NULL ){
                val_2 = list_iterator_next(li, 'l');

                list_increment(matrix->lines[l], matrix->columns[index_1], l, index_1, *val_2);
                list_decrement(matrix->lines[l], matrix->columns[index_2], l, index_2);

                break;

            } else if( list_iterator_return_place(li, list_type) > index_2 && val_1 != NULL ){

                list_increment(matrix->lines[l], matrix->columns[index_2], l, index_2, *val_1);
                list_decrement(matrix->lines[l], matrix->columns[index_1], l, index_1);

                break;
                
            } else {
                list_iterator_next(li, 'l');
          }          
        }
        free(li);
    }


}

void matrix_swap_lines(Matrix *matrix, int index_1, int index_2, char list_type){ 
    
    for( int c = 0; c < matrix->number_columns; c++ ){
        ListIterator *li = list_front_iterator(matrix->columns[c]);
        data_type *val_1 = NULL, *val_2 = NULL, aux;


        while( !list_iterator_is_over(li) ){
            
            if( list_iterator_return_place(li, list_type) == index_1 ){
                val_1 = list_iterator_next(li, 'c');

            } else if( list_iterator_return_place(li, list_type) == index_2 && val_1 != NULL ){
                val_2 = list_iterator_next(li, 'c');
                
                aux = *val_2;
                *val_2 = *val_1;
                *val_1 = aux;

                break;

            } else if( list_iterator_return_place(li, list_type) == index_2 && val_1 == NULL ){
                val_2 = list_iterator_next(li, 'c');

                list_increment(matrix->lines[index_1], matrix->columns[c], index_1, c, *val_2);
                list_decrement(matrix->lines[index_2], matrix->columns[c], index_2, c);

                break;

            } else if( list_iterator_return_place(li, list_type) > index_2 && val_1 != NULL ){

                list_increment(matrix->lines[index_2], matrix->columns[c], index_2, c, *val_1);
                list_decrement(matrix->lines[index_1], matrix->columns[c], index_1, c);

                break;
                
            } else {
                list_iterator_next(li, 'c');
          }          
        }
        free(li);
    }


}

// void matrix_swap_columns(Matrix *matrix, int index_1, int index_2, char list_type){ 
//     List **row = NULL;
//     int *r, *l1, *l2, *c1, *c2;
//     int qty_rows = 0;
//     char type_next;


//     if( list_type == 'c' ){
//         qty_rows = matrix->number_lines;
//         row = matrix->lines;
//         type_next = 'l';
//         l1 = l2 = r;
//         c1 = index_1, c2 = index_2;

//     } else if( list_type == ' l' ){
//         qty_rows = matrix->number_columns;
//         row = matrix->columns;
//         type_next = 'c';
//         c1 = c2 = r;
//         l1 = index_1, l2 = index_2;
//     } 

    
//     for( *r = 0; *r < qty_rows; *r++ ){
//         ListIterator *li = list_front_iterator(row[*r]);
//         data_type *val_1 = NULL, *val_2 = NULL, aux;

//         while( !list_iterator_is_over(li) ){
            
//             if( list_iterator_return_place(li, list_type) == index_1 ){
//                 val_1 = list_iterator_next(li, type_next);

//             } else if( list_iterator_return_place(li, list_type) == index_2 && val_1 != NULL ){
//                 val_2 = list_iterator_next(li, type_next);
                
//                 aux = *val_2;
//                 *val_2 = *val_1;
//                 *val_1 = aux;

//                 break;

//             } else if( list_iterator_return_place(li, list_type) == index_2 && val_1 == NULL ){
//                 val_2 = list_iterator_next(li, type_next);

//                 list_increment(matrix->lines[*l1], matrix->columns[*c1], *l1, *c1, *val_2);
//                 list_decrement(matrix->lines[*l2], matrix->columns[*c2], *l2, *c2);

//                 break;

//             } else if( list_iterator_return_place(li, list_type) > index_2 && val_1 != NULL ){

//                 list_increment(matrix->lines[*l2], matrix->columns[*c2], *l2, *c2, *val_1);
//                 list_decrement(matrix->lines[*l1], matrix->columns[*c1], *l1, *c1);

//                 break;
                
//             } else {
//                 list_iterator_next(li, type_next);
//           }          
//         }
//         free(li);
//     }


// }


void matrix_transposed(Matrix **matrix, int index){

    int qty_lines = matrix[index]->number_columns;
    int qty_columns = matrix[index]->number_lines;

    matrix = matrix_construct(matrix, qty_lines, qty_columns);
    int new_index = matrix[0]->quantity-1;

    for( int l = 0; l < matrix[index]->number_lines; l++ ){
        ListIterator *li = list_front_iterator(matrix[index]->lines[l]);

        while( !list_iterator_is_over(li) ){
            int c = list_iterator_return_place(li, 'c');
            data_type val = *list_iterator_next(li, 'l');
            
            list_increment(matrix[new_index]->lines[c], matrix[new_index]->columns[l], c, l, val);
        }

        free(li);
    }
}












void print_dense_matrix(Matrix *matrix){
    ListIterator *li = NULL;
    data_type value = 0;
    int p = -1;

    for( int l = 0; l < matrix->number_lines; l++ ){
        li = list_front_iterator(matrix->lines[l]);
        p = -1;

        for( int c = 0; c < matrix->number_columns; c++ ){
            // data_type *value = (data_type*) malloc(sizeof(data_type));

            if( !list_iterator_is_over(li) )
                p = list_iterator_return_place(li, 'c');

            if( p == c ){
                value = *list_iterator_next(li, 'l');

            } else {
                value = 0;
            } 
 
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
    // int p = -1;

    for( int l = 0; l < matrix->number_lines; l++ ){
        li = list_front_iterator(matrix->lines[l]);

        while( !list_iterator_is_over(li) ){
            value = *list_iterator_next(li, 'l');
            printf("%.0f ", value);
        }
                 
        free(li);
        printf("\n");
    }
    printf("\n");
}

// Matrix *read_binary_matrix(){
//     char path[11] = PATH_FILE;
//     FILE *arq = fopen(path, "rb");

//     if( !arq ){
//         printf("ERROR: couldn't open the file!\n");
//         exit(1);
//     }
//     printf("File open!\n");  

//     Matrix *matrix = (Matrix*) malloc( sizeof(Matrix) );

//     fread( &matrix->number_lines, sizeof(int), 1, arq);
//     fread( &matrix->number_columns, sizeof(int), 1, arq);
//     fread( &matrix->qty_allocated, sizeof(int), 1, arq);
//     fread( &matrix->quantity, sizeof(int), 1, arq);
// }

void save_binary_matrix(Matrix *matrix){
    char path[11] = PATH_FILE;
    FILE *arq = fopen(path, "wb");

    if( !arq ){
        printf("ERROR: couldn't open the file!\n");
        exit(1);
    }
    printf("File open!\n");    

    fwrite( &matrix->number_lines, sizeof(int), 1, arq);
    fwrite( &matrix->number_columns, sizeof(int), 1, arq);

    for( int i = 0; i < matrix->number_lines; i++ )
        save_binary_list(arq, matrix->lines[i]);

    fclose(arq);
}