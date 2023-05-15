#include "../headers/matrix.h"

struct Matrix{
    List_pt *lines;
    List_pt *columns;
    int number_lines;
    int number_columns;
    int qty_allocated;
    int quantity;
};

Matrix_pt *create_matrix(Matrix_pt *matrix){
    int l = 0, c = 0;

    while(1){
        printf("Quantity of lines and columns of the desired matrix, respectively: ");
        scanf("%d %d", &l, &c);

        if( l <= 0 || c <= 0 )
            printf("Please, type numbers above zero!\n\n");
        else 
            break;        
    }

    matrix = matrix_construct(matrix, l, c);

    return matrix;
}

Matrix_pt *matrix_construct(Matrix_pt *matrix, int qty_lines, int qty_columns){
    int i = 0, qty = 0;

    if( matrix != NULL )
        qty = matrix[0]->quantity;

    matrix = matrix_alloc_and_realloc(matrix, qty); 
    matrix_verify(matrix);

    matrix = matrix_initialize(matrix, qty_lines, qty_columns);

    int index = matrix[0]->quantity-1;

    matrix[index]->lines = list_construct( matrix[index]->lines, matrix[index]->number_lines );
    matrix[index]->columns = list_construct( matrix[index]->lines, matrix[index]->number_columns );

    return matrix;
}

Matrix_pt *matrix_alloc_and_realloc(Matrix_pt *matrix, int qty_matrices){
    int i = 0, inicial_qty = 0;

    if( !qty_matrices ){
        matrix = (Matrix_pt*) malloc( QTY_ALLOC_INITIALLY * sizeof(Matrix_pt) ); 

        for( i = inicial_qty; i < QTY_ALLOC_INITIALLY; i++ ){
            matrix[i] = (Matrix_pt) malloc( sizeof(Matrix) );
        }

        matrix[0]->qty_allocated = QTY_ALLOC_INITIALLY;
        matrix[0]->quantity = 0;

    } else if( qty_matrices == matrix[0]->qty_allocated ) {
        inicial_qty = matrix[0]->qty_allocated;
        matrix[0]->qty_allocated *= 2;

        matrix = realloc( matrix, matrix[0]->qty_allocated * sizeof(Matrix_pt) );

        for( i = inicial_qty; i < matrix[0]->qty_allocated; i++ ){
            matrix[i] = (Matrix_pt) malloc( sizeof(Matrix) );
        }
    }

    return matrix;
}

Matrix_pt *matrix_initialize(Matrix_pt *matrix, int l, int c){
    
    matrix[matrix[0]->quantity]->number_lines = l;
    matrix[matrix[0]->quantity]->number_columns = c;
    matrix[0]->quantity++;

    return matrix;
}

void matrix_verify(Matrix_pt *matrix){

    if( matrix != NULL ){
        printf("The matrix-%d was constructed!\n\n", matrix[0]->quantity);

    } else {
        printf("ERROR: failure to build the matrix.\n\n");
        exit(1);
    }
}

void destroy_matrix(Matrix_pt *matrix){
    int qty_alloc = matrix[0]->qty_allocated;
    int qty_matrices = matrix[0]->quantity;

    for( int i = 0; i < qty_alloc; i++ ){
        // printf("NL %d NC %d", matrix[i]->number_lines,  matrix[i]->number_columns);

        if( i < qty_matrices ){
            list_destroy(matrix[i]->lines, matrix[i]->number_lines, 'l');
            list_destroy(matrix[i]->columns, matrix[i]->number_columns, 'c');
        }
       
        free(matrix[i]);
    }
    free(matrix);
}

// nao permitir adicionar valor sem que uma matriz tenha sido criada
void assign_value_matrix(Matrix_pt *matrix){
    data_type val = 0;
    
    int index = matrix_return_index(matrix);

    int l = matrix_return_position(matrix, index,'l');
    int c = matrix_return_position(matrix, index,'c');

    printf("\nValue of the node: ");
    scanf("%f", &val);

    int position_occupied = verify_position_occupied(matrix[index]->lines[l], c, 'c');

    if( position_occupied && val != 0 )
        list_assign_value(matrix[index]->lines[l], c, val, 'p');

    else if( position_occupied && val == 0 )
        list_decrement(matrix[index]->lines[l], matrix[index]->columns[c], l, c);

    else if( !position_occupied && val != 0 )
        list_increment(matrix[index]->lines[l], matrix[index]->columns[c], l, c, val);

}

int matrix_return_index(Matrix_pt *matrix){
    int index = 0;

    if( matrix[0]->quantity == 1 )
        printf("\n|Available index: 0\n");
    else
        printf("\n|Available indexes: 0 to %d\n", matrix[0]->quantity-1);

    while(1){
        printf("Matrix that you are interested: ");
        scanf("%d", &index);

        if( index < 0 || index >= matrix[0]->quantity )
            printf("Please, type an available index!\n\n");
        else
            return index;
    }

}

int matrix_return_position(Matrix_pt *matrix, int index, char position_type){
    int p = 0;

    switch( position_type ){

        case 'l':
            if( matrix[index]->number_lines == 1 )
                printf("\n|Available line: 0\n");
            else
                printf("\n|Available lines: 0 to %d\n", matrix[index]->number_lines-1);

            while(1){
                printf("Line of the node: ");
                scanf("%d", &p);  

                if( p < 0 || p >= matrix[index]->number_lines )
                    printf("Please, type an available line!\n\n");
                else
                    break;
            }
            break;

        case 'c':
            if( matrix[index]->number_columns == 1 )
                printf("\n|Available column: 0\n");
            else
                printf("\n|Available columns: 0 to %d\n", matrix[index]->number_columns-1);

            while(1){
                printf("Column of the node: ");
                scanf("%d", &p);  

                if( p < 0 || p >= matrix[index]->number_columns )
                    printf("Please, type an available column!\n\n");
                else 
                    break;
            }
            break;
    }

    return p;
}

void read_node_value_matrix(Matrix_pt *matrix){

    int index = matrix_return_index(matrix);

    int l = matrix_return_position(matrix, index, 'l');
    int c = matrix_return_position(matrix, index, 'c');

    Node_pt n = find_node_row(matrix[index]->lines[l], c, 'a', 'l', 'c');

    if( n == NULL )
        printf("Value of the node [%d,%d]: %f\n\n", l, c, 0.0);
    else
        printf("Value of the node [%d,%d]: %f\n\n", l, c, node_return_value(n));
}

//mostrar quais matrizes têm o msm tamanho
// ta percorrendo as listas toda hora MUDAR
void add_matrices(Matrix_pt *matrix){

    printf("\n|ADD TWO MATRICES|\n");

    int index_1 = matrix_return_index(matrix);
    int qty_lines = matrix[index_1]->number_lines;
    int qty_columns = matrix[index_1]->number_columns;

    int index_2 = matrix_return_index_2(matrix, qty_lines, qty_columns);

    matrix = matrix_construct(matrix, qty_lines, qty_columns);
    int new_index = matrix[0]->quantity-1;

    data_type value = 0;
    ListIterator_pt li = NULL;
    Node_pt current_node = NULL;
    int size_line = 0, c = 0;

    // *matrix[new_index] = *matrix[index_1];
    // memcpy(matrix[new_index], matrix[index_1], sizeof(Matrix));

    // print_dense_matrix(matrix);


    for( int l = 0; l < qty_lines; l++ ){
        li = list_front_iterator(matrix[index_1]->lines[l]);
        size_line = list_return_size(matrix[index_1]->lines[l]);

        for( int p = 0; p < size_line; p++ ){
            current_node = list_iterator_return_current(li, 'l');

            value = node_return_value(current_node);
            c = node_return_place(current_node, 'c');

            list_increment(matrix[new_index]->lines[l], matrix[new_index]->columns[c], l, c, value);
        }
    }

    print_dense_matrix(matrix);

    // for( int l = 0; l < qty_lines; l++ ){
    //     li_1 = list_front_iterator(matrix[index_1]->lines[l]);
    //     li_2 = list_front_iterator(matrix[index_2]->lines[l]);

    //     for( int c = 0; c < qty_columns; c++ ){ 
    //         value_1 = list_return_value(matrix[index_1]->lines[l], c, 'c');
    //         value_2 = list_return_value(matrix[index_2]->lines[l], c, 'c');

    //         new_value = value_1 + value_2;

    //         printf("NEW %.0f\n", new_value);

    //         if( new_value != 0 )
    //             list_increment(matrix[new_index]->lines[l], matrix[new_index]->columns[c], l, c, new_value);
    //     }

    //     free(li_1);
    //     free(li_2);
    // }

}

// void add_matrices(Matrix_pt *matrix){

//     printf("\n|ADD TWO MATRICES|\n");

//     int index_1 = matrix_return_index(matrix);
//     int qty_lines = matrix[index_1]->number_lines;
//     int qty_columns = matrix[index_1]->number_columns;

//     int index_2 = matrix_return_index_2(matrix, qty_lines, qty_columns);

//     matrix = matrix_construct(matrix, qty_lines, qty_columns);
//     int new_index = matrix[0]->quantity-1;

//     data_type value_1 = 0, value_2 = 0, new_value = 0;
//     ListIterator_pt li_1 = NULL, li_2 = NULL;
//     int size_line = 0;

//     // *matrix[new_index] = *matrix[index_1];
//     // memcpy(matrix[new_index], matrix[index_1], sizeof(Matrix));

//     // print_dense_matrix(matrix);


//     for( int l = 0; l < qty_lines; l++ ){
        
//         size_line = list_return_size(matrix[index_1]->lines[l]);

//         for( int p = 0; p < size_line; p++ ){
            
//         }
//     }


//     for( int l = 0; l < qty_lines; l++ ){
//         li_1 = list_front_iterator(matrix[index_1]->lines[l]);
//         li_2 = list_front_iterator(matrix[index_2]->lines[l]);

//         for( int c = 0; c < qty_columns; c++ ){ 
//             value_1 = list_return_value(matrix[index_1]->lines[l], c, 'c');
//             value_2 = list_return_value(matrix[index_2]->lines[l], c, 'c');

//             new_value = value_1 + value_2;

//             printf("NEW %.0f\n", new_value);

//             if( new_value != 0 )
//                 list_increment(matrix[new_index]->lines[l], matrix[new_index]->columns[c], l, c, new_value);
//         }

//         free(li_1);
//         free(li_2);
//     }

// }

int matrix_return_index_2(Matrix_pt *matrix, int qty_lines, int qty_columns){
    int index_2 = 0;

    while(1){
        index_2 = matrix_return_index(matrix);

        if( matrix[index_2]->number_lines != qty_lines || 
        matrix[index_2]->number_columns != qty_columns )
            ("Please, type an matrix with %d lines and %d columns!\n\n", qty_lines, qty_columns);

        else
            break;
    }

    return index_2;
}

// ta percorrendo o vetor inteiro, mudar isso
void print_dense_matrix(Matrix_pt *matrix){
    ListIterator_pt li = NULL;
    data_type value = 0;

    int index = matrix_return_index(matrix);

    int qty_lines = matrix[index]->number_lines;
    int qty_columns = matrix[index]->number_columns;

    for( int l = 0; l < qty_lines; l++ ){
        li = list_front_iterator(matrix[index]->lines[l]);

        for( int c = 0; c < qty_columns; c++ ){
            value = list_return_value(li, c, 'c');

            // printf("%.1f ", value);
        }
        printf("\n");
        free(li);
    }
}

// // ta percorrendo o vetor inteiro, mudar isso
// void print_dense_matrix(Matrix_pt *matrix){
//     ListIterator_pt li = NULL;
//     data_type value = 0;

//     int index = matrix_return_index(matrix);

//     int qty_lines = matrix[index]->number_lines;
//     int qty_columns = matrix[index]->number_columns;

//     for( int l = 0; l < qty_lines; l++ ){
//         li = list_front_iterator(matrix[index]->lines[l]);

//         for( int c = 0; c < qty_columns; c++ ){
//             value = list_return_value(li, c, 'c');

//             // printf("%.1f ", value);
//         }
//         printf("\n");
//         free(li);
//     }
// }