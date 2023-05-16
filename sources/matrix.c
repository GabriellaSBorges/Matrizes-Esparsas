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

Matrix **matrix_assign_value(Matrix **matrix, int index, int l, int c, data_type val){
    
    int position_occupied = verify_position_occupied(matrix[index]->lines[l], c, 'c');

    if( position_occupied && val != 0 )
        list_assign_value(matrix[index]->lines[l], c, val, 'p');

    else if( position_occupied && val == 0 )
        list_decrement(matrix[index]->lines[l], matrix[index]->columns[c], l, c);

    else if( !position_occupied && val != 0 )
        list_increment(matrix[index]->lines[l], matrix[index]->columns[c], l, c, val);

    return matrix;
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
    data_type *value_1 = 0, *value_2 = 0, *new_value = 0;
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

                        value_1 = list_iterator_next(li_1, 'c');
                        value_2 = list_iterator_next(li_2, 'c');

                        *new_value = *value_1 + *value_2;
                        list_increment(matrix[new_index]->lines[l], matrix[new_index]->columns[c], l, c, *new_value);

                    } else if( !list_iterator_is_over(li_1) && (list_iterator_is_over(li_2)  ||
                    list_iterator_return_place(li_1, 'c') < list_iterator_return_place(li_2, 'c')) ){
                        c = list_iterator_return_place(li_1, 'c');
                        new_value = list_iterator_next(li_1, 'c');

                        list_increment(matrix[new_index]->lines[l], matrix[new_index]->columns[c], l, c, *new_value);

                    } else if ( list_iterator_is_over(li_1) && (!list_iterator_is_over(li_2) ||
                    list_iterator_return_place(li_1, 'c') > list_iterator_return_place(li_2, 'c')) ){
                        c = list_iterator_return_place(li_2, 'c');
                        new_value = list_iterator_next(li_2, 'c');

                        list_increment(matrix[new_index]->lines[l], matrix[new_index]->columns[c], l, c, *new_value);
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
            val = list_iterator_next(li, 'c');
            (*val) *= scalar;
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
                value = *list_iterator_next(li, 'c');

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
