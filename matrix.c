#include "matrix.h"

struct Matrix{
    List_pt *lines;
    List_pt *columns;
    int number_lines;
    int number_columns;
    int qty_allocated;
    int quantity;
};

void create_matrix(Matrix_pt matrix){
    int l = 0, c = 0;

    while(1){
        printf("Quantity of lines and columns of the desired matrix, respectively: ");
        scanf("%d %d", &l, &c);

        if( l <= 0 || c <= 0 )
            printf("Please, type numbers above zero!\n\n");
        else 
            break;        
    }

    matrix_construct(matrix, l, c);

}

void *matrix_construct(Matrix_pt *matrix, int qty_lines, int qty_columns){
    int i = 0, qty = 0;

    if( matrix != NULL )
        qty = matrix[0]->quantity;

    matrix = matrix_alloc_and_realloc(matrix, qty); 
    matrix = matrix_initialize(matrix, qty_lines, qty_columns);

    int index = matrix[0]->quantity-1;

    // printf("VAL %d %d\n", matrix[index]->number_lines, matrix[index]->number_columns);
    // printf("Q %d  A %d\n", matrix[0]->quantity, matrix[0]->qty_allocated);

    matrix[index]->lines = list_construct( matrix[index]->lines, matrix[index]->number_lines );
    matrix[index]->columns = list_construct( matrix[index]->lines, matrix[index]->number_columns );

    matrix_verify(matrix);
}

void *matrix_alloc_and_realloc(Matrix_pt *matrix, int qty_matrices){
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
}

void *matrix_initialize(Matrix_pt *matrix, int l, int c){
    
    matrix[matrix[0]->quantity]->number_lines = l;
    matrix[matrix[0]->quantity]->number_columns = c;
    matrix[0]->quantity++;
}

void matrix_verify(Matrix_pt *matrix){

    if( matrix != NULL ){
        printf("The matrix-%d was constructed!\n\n", matrix[0]->quantity-1);

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

void add_matrices(Matrix_pt *matrix){
    printf("|ADD TWO MATRICES|\n");

    int index_1 = matrix_return_index(matrix);
    int qty_lines = matrix[index_1]->number_lines;
    int qty_columns = matrix[index_1]->number_columns;

    while(){
        int index_2 = matrix_return_index(matrix);
    }
    

    matrix_construct(matrix);
}

// Matrix_pt (Matrix_pt matrix_1, Matrix_pt matrix_2) {

// }