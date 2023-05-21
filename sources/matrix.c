#include "../headers/matrix.h"

struct Matrix{
    List **lines;
    List **columns;
    int number_lines;
    int number_columns;
};

/*
Complexidade: O(L + C)
l = número de linhas; c = número de colunas
-> Percorre o conjunto de linhas e de colunas, inicializando cada uma.
*/
Matrix *matrix_construct(int *qty_matrices, int qty_lines, int qty_columns, char hide_print){

    Matrix *matrix = (Matrix*) malloc( sizeof(Matrix) );

    matrix->number_lines = qty_lines;
    matrix->number_columns = qty_columns;
    (*qty_matrices)++;

    if( matrix != NULL && hide_print == 0 ){
        printf("\n|Matrix-%d was constructed!\n\n", (*qty_matrices)-1);

    } else if( !matrix ) {
        printf("ERROR: failure to build the matrix.\n\n");
        exit(1);
    }

    /* Aloca memória para cada lista das linhas e das colunas da matriz */
    matrix->lines = list_construct( matrix->number_lines );
    matrix->columns = list_construct( matrix->number_columns );

    return matrix;
}

/*
Complexidade: O(L*nL + C)
L = número de linhas; nL = qtd máxima de nodes em uma linha; C = número de colunas
-> Percorre todas as linhas e destrói cada um de seus nodes, depois acessa e libera a head de cada coluna.
*/
void matrix_destroy(Matrix *matrix){

    if( matrix ){
        list_destroy(matrix->lines, matrix->number_lines, 'l');
        list_destroy(matrix->columns, matrix->number_columns, 'c');

        free(matrix);
    }
}

/*
Complexidade: O(2nL + nC)
nL = qtd máxima de nodes em uma linha L; nC = qtd máxima de nodes em uma coluna C

-> No pior caso, percorre a linha procurando o node desejado mas não o acha, então cria um:
percorre a linha até encontrar o node antes do novo, o mesmo ocorre com a coluna. 
*/
void matrix_assign_value(Matrix *matrix, int l, int c, data_type val){

    /* Procura o node desejado */
    Node *node = list_find_node(matrix->lines[l], c, 'a', 'l', 'c');

    /* Se ele já estiver alocado e o valor for diferente de 0, trocar o valor */
    if( node && val )
        node_assign_value(node, val);

    /* Se estiver alocado mas o valor for 0, remover o node */
    else if( node && !val )
        list_decrement(matrix->lines[l], matrix->columns[c], l, c);

    /* Se ainda não estiver ocupado e o valor for diferente de 0, criar um novo node */
    else if( !node && val )
        list_increment(matrix->lines[l], matrix->columns[c], l, c, val);
}

/*
Complexidade: O(nL)
nL = qtd máxima de nodes em uma linha L
-> Itera sobre uma linha até encontrar o node desejado
*/
void matrix_read_value(Matrix *matrix, int index, int l, int c){

    Node *n = list_find_node(matrix->lines[l], c, 'a', 'l', 'c');
    data_type *val = node_return_value(n);

    if( !n )
        printf("> Value of the node [%d,%d] in matrix '%d': %.1f\n\n", l, c, index, 0.0);
    else
        printf("> Value of the node [%d,%d] in matrix '%d': %.1f\n\n", l, c, index, *val);
}

/*
Complexidade: O((L + C) + (L1*nL1 + L2*nL2)*(nL + nC)) = O(a + (L1*nL1 + L2*nL2)*i)
a =  complexidade de matrix_construct ( O(L + C) ); i = complexidade de list_increment ( O(nL + nC) );
L1 = número de linhas da matriz 1; nL1 = qtd máxima de nodes na linha L1; L2 = número de linhas da matriz 2; nL2 = qtd máxima de nodes na linha L2;
L = número de linhas da nova matriz; nL = qtd máxima de nodes na linha L; C = número de colunas da nova matriz; nC = qtd máxima de nodes na coluna C;

-> Cria uma nova matriz. Para cada linha de cada uma das duas matrizes(1 e 2), itera sobre seus nodes e, quando achar uma posicao ocupada em pelo menos uma das linhas, 
incrementa na nova matriz: percorre a linha e a coluna correspondente na nova matriz até achar o prev node.
*/
Matrix *add_matrices(Matrix *matrix_1, Matrix *matrix_2, int *qty_matrices){
    data_type new_value = 0;

    printf("\n================|ADD MATRICES|================\n");

    if( matrix_1->number_lines != matrix_2->number_lines || matrix_1->number_columns != matrix_2->number_columns ){
        printf("Matrices of different sizes cannot be added!\n\n");
        return NULL;
    }      
        

    Matrix *new_matrix = matrix_construct(qty_matrices, matrix_1->number_lines, matrix_1->number_columns, 0);

    /* Para cada linha, cria um iterador para a matriz 1 e outro para a matriz 2 */
    for( int l = 0; l < matrix_1->number_lines; l++ ){
        ListIterator *li_1 = list_front_iterator(matrix_1->lines[l]);
        ListIterator *li_2 = list_front_iterator(matrix_2->lines[l]);

        /* Itera sobre as listas simultaneamente e, a partir das posições das colunas, incrementa a nova matriz */
        while( !list_iterator_is_over(li_1) || !list_iterator_is_over(li_2) ){
            int column_li1 = !list_iterator_is_over(li_1) ? list_iterator_return_place(li_1, 'c') : -1;
            int column_li2 = !list_iterator_is_over(li_2) ? list_iterator_return_place(li_2, 'c') : -1;


                /* Se tiver nodes na mesma posição nas duas matizes -> soma e preenche */
                if( column_li1 == column_li2 ){

                    new_value = *list_iterator_next(li_1, 'l') + *list_iterator_next(li_2, 'l');
                    list_increment(new_matrix->lines[l], new_matrix->columns[column_li1], l, column_li1, new_value);

                /* Node apenas na matriz 1 -> preenche */
                } else if( (!list_iterator_is_over(li_1) && list_iterator_is_over(li_2)) || 
                (column_li1 < column_li2 && column_li1 != -1) ){

                    new_value = *list_iterator_next(li_1, 'l');
                    list_increment(new_matrix->lines[l], new_matrix->columns[column_li1], l, column_li1, new_value);

                /* Node apenas na matriz 2 -> preenche */
                } else if( (list_iterator_is_over(li_1) && !list_iterator_is_over(li_2)) || 
                (column_li1 > column_li2 && column_li2 != -1 ) ){

                    new_value = *list_iterator_next(li_2, 'l');
                    list_increment(new_matrix->lines[l], new_matrix->columns[column_li2], l, column_li2, new_value);
                }     
        }  
        free(li_1);
        free(li_2);            
    }

    return new_matrix;
}

/*
Complexidade: O((L + C) + L1*nL1*(nL + nC)) = O(a + L1*nL1*i)
a =  complexidade de matrix_construct ( O(L + C); i = complexidade de list_increment ( O(nL + nC) );
L1 = número de linhas da matriz 1; nL1 = qtd máxima de nodes na linha L1
L = número de linhas da nova matriz; nL = qtd máxima de nodes na linha L; C = número de colunas da nova matriz; nC = qtd máxima de nodes na coluna C;

-> Cria uma nova matriz. Percorre cada node de cada linha da matriz1 e incrementa o valor correspondente na matriz2.
*/
Matrix *matrix_multiply_by_scalar(Matrix *matrix, int *qty_matrices, data_type scalar){
    ListIterator *li = NULL;

    printf("\n=============|MULTIPLY BY SCALAR|=============\n");

    Matrix *new_matrix = matrix_construct(qty_matrices, matrix->number_lines, matrix->number_columns, 0);

    /* Itera sobre cada linha da matriz base, multiplica seus itens pelo escalar e incrementa na nova matriz */
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

/*
Complexidade: O((L + C) + (L1*nL1)*(C2*nC2)*(nL + nC)) = O(a + (L1*nL1)*(C2*nC2)**i )
a =  complexidade de matrix_construct ( O(L + C) ); i = complexidade de list_increment ( O(nL + nC) );
L1 = número de linhas da matriz 1; nL1 = qtd máxima de nodes na linha L1; C2 = número de colunas da matriz 2; nC2 = qtd máxima de nodes na coluna L2;
L = número de linhas da nova matriz; nL = qtd máxima de nodes na linha L; C = número de colunas da nova matriz; nC = qtd máxima de nodes na coluna C;

Cria uma nova matriz. Para cada linha da matriz1, percorre cada coluna da matriz2 e incrementa o novo valor na nova matriz.
*/
Matrix *matrices_multiply(Matrix *matrix_1, Matrix *matrix_2, int *qty_matrices){

    printf("\n=============|MULTIPLY MATRICES|=============\n");

    if( matrix_1->number_columns != matrix_2->number_lines ){
        printf("These matrices cannot be multiplied!\n\n");
        return NULL;
    }  


    Matrix *new_matrix = matrix_construct(qty_matrices, matrix_1->number_lines, matrix_2->number_columns, 0);

    /* Para cada iterador de uma linha da matriz 1, cria um iterador para cada coluna da matriz 2 */
    for( int l = 0; l < matrix_1->number_lines; l++ ){ 
        for( int c = 0; c < matrix_2->number_columns; c++ ){
            ListIterator *li_1 = list_front_iterator(matrix_1->lines[l]);
            ListIterator *li_2 = list_front_iterator(matrix_2->columns[c]);
            data_type new_value = 0;

            /* Enquanto nenhuma das listas é nula, soma as multiplicações um elemento da matriz 1 pelo correspondente da matriz 2 */
            while( !list_iterator_is_over(li_1) && !list_iterator_is_over(li_2) ){

                if( list_iterator_return_place(li_1, 'c') == list_iterator_return_place(li_2, 'l') ){
                    new_value += (*list_iterator_next(li_1, 'l')) * (*list_iterator_next(li_2, 'c'));

                /* Se uma das matrizes não tiver um node na posição X, ela será 0 (não incrementar) */
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

/*
Complexidade: O((L + C) + (L1*nL1 + L2*nL2)*(nL + nC)) = O(a + (L1*nL1 + L2*nL2)*i)
a =  complexidade de matrix_construct ( O(L + C) ); i = complexidade de list_increment ( O(nL + nC) );
L1 = número de linhas da matriz 1; nL1 = qtd máxima de nodes na linha L1; L2 = número de linhas da matriz 2; nL2 = qtd máxima de nodes na linha L2;
L = número de linhas da nova matriz; nL = qtd máxima de nodes na linha L; C = número de colunas da nova matriz; nC = qtd máxima de nodes na coluna C;

-> Cria uma nova matriz. Para cada linha de cada uma das duas matrizes(1 e 2), itera sobre seus nodes e, quando achar uma posicao ocupada nas duas linhas, 
incrementa na nova matriz.
*/
Matrix *multiply_point_to_point(Matrix *matrix_1, Matrix *matrix_2, int *qty_matrices, char hide_print){

    hide_print == 0 ? printf("\n==========|MULTIPLY POINT TO POINT|==========\n") : 1;

    if( matrix_1->number_lines != matrix_2->number_lines || matrix_1->number_columns != matrix_2->number_columns ){
        printf("These matrices cannot be multiplied!\n\n");
        return NULL;
    }


    Matrix *new_matrix = matrix_construct(qty_matrices, matrix_1->number_lines, matrix_2->number_columns, hide_print);

    /* Para cada linha, cria um iterador para a matriz 1 e outro para a matriz 2 */
    for( int l = 0; l < matrix_1->number_lines; l++ ){ 
        ListIterator *li_1 = list_front_iterator(matrix_1->lines[l]);
        ListIterator *li_2 = list_front_iterator(matrix_2->lines[l]);

        /* Enquanto nenhuma das listas é nula, multiplica um elemento da matriz 1 pelo correspondente na matriz 2 */
        while( !list_iterator_is_over(li_1) && !list_iterator_is_over(li_2) ){

            /* Posição ocupada nas duas matrizes -> multiplica os valores e incrementa */
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

/*
Complexidade: O(L*nL + L*((nL + nC) + nL)) = O(L*nL + L*(i + d))
i = complexidade de list_increment ( O(nL + nC) ); d = complexidade de list_decrement ( O(nL) );
L = número de linhas; nL = qtd máxima de nodes em uma linha; nC = qtd máxima de nodes em uma coluna

-> Itera sobre cada linha da matriz. No pior caso, em cada linha um node será incrementado e outro será decrementado.
*/
void matrix_swap_columns(Matrix *matrix, int index_1, int index_2){ 

    printf("\n===============|SWAP COLUMNS|===============\n");
    
    /* Itera sobre cada linha da matriz e procura o node1 (coluna = index_1) e o node2 (coluna = index_2) */
    for( int l = 0; l < matrix->number_lines; l++ ){
        ListIterator *li = list_front_iterator(matrix->lines[l]);
        data_type *val_1 = NULL, *val_2 = NULL, aux;
        int swap_confirm = 0;

        while( !list_iterator_is_over(li) ){
            
            if( list_iterator_return_place(li, 'c') == index_1 ){
                val_1 = list_iterator_next(li, 'l');

            /* Se as posições 1 e 2 estiverem ocupadas, trocar seus valores */
            } else if( list_iterator_return_place(li, 'c') == index_2 && val_1 ){
                val_2 = list_iterator_next(li, 'l');
                
                aux = *val_2;
                *val_2 = *val_1;
                *val_1 = aux;

                swap_confirm++;
                break;

            /* Se não tiver um node na posição 1, mas na 2 sim, incrementar a 1 e remover o node da 2 */
            } else if( list_iterator_return_place(li, 'c') == index_2 && !val_1 ){
                val_2 = list_iterator_next(li, 'l');

                list_increment(matrix->lines[l], matrix->columns[index_1], l, index_1, *val_2);
                list_decrement(matrix->lines[l], matrix->columns[index_2], l, index_2);
                
                swap_confirm++;
                break;

            /* Se não tiver um node na posição 2, mas na 1 sim, incrementar a 2 e remover o node da 1 */
            } else if( list_iterator_return_place(li, 'c') > index_2 && val_1 ){

                list_increment(matrix->lines[l], matrix->columns[index_2], l, index_2, *val_1);
                list_decrement(matrix->lines[l], matrix->columns[index_1], l, index_1);

                swap_confirm++;
                break;
                
            } else {
                list_iterator_next(li, 'l');
          }          
        }

        /* se a lista acabou antes de chegar ao índice 2, realiza o swap */
        if( val_1 && !swap_confirm ){
            list_increment(matrix->lines[l], matrix->columns[index_2], l, index_2, *val_1);
            list_decrement(matrix->lines[l], matrix->columns[index_1], l, index_1);
        }

        free(li);
    }
}

/*
Complexidade: O(C*nC + C*((nL + nC) + nL)) = O(C*nC + C*(i + d))
i = complexidade de list_increment ( O(nL + nC) ); d = complexidade de list_decrement ( O(nL) );
C = número de colunas; nC = qtd máxima de nodes em uma coluna; nL = qtd máxima de nodes em uma linha

-> Itera sobre cada coluna da matriz. No pior caso, em cada coluna um node será incrementado e outro será decrementado.
*/
void matrix_swap_lines(Matrix *matrix, int index_1, int index_2){ 

    printf("\n================|SWAP LINES|================\n");
    
    /* Itera sobre cada coluna da matriz e procura o node1 (linha = index_1) e o node2 (linha = index_2) */
    for( int c = 0; c < matrix->number_columns; c++ ){
        ListIterator *li = list_front_iterator(matrix->columns[c]);
        data_type *val_1 = NULL, *val_2 = NULL, aux;
        int swap_confirm = 0;

        while( !list_iterator_is_over(li) ){
            
            if( list_iterator_return_place(li, 'l') == index_1 ){
                val_1 = list_iterator_next(li, 'c');

            /* Se as posições 1 e 2 estiverem ocupadas, trocar seus valores */
            } else if( list_iterator_return_place(li, 'l') == index_2 && val_1 ){
                val_2 = list_iterator_next(li, 'c');
                
                aux = *val_2;
                *val_2 = *val_1;
                *val_1 = aux;

                swap_confirm++;
                break;

            /* Se não tiver um node na posição 1, mas na 2 sim, incrementar a 1 e remover o node da 2 */
            } else if( list_iterator_return_place(li, 'l') == index_2 && !val_1 ){
                val_2 = list_iterator_next(li, 'c');

                list_increment(matrix->lines[index_1], matrix->columns[c], index_1, c, *val_2);
                list_decrement(matrix->lines[index_2], matrix->columns[c], index_2, c);

                swap_confirm++;
                break;

            /* Se não tiver um node na posição 2, mas na 1 sim, incrementar a 2 e remover o node da 1 */
            } else if( list_iterator_return_place(li, 'l') > index_2 && val_1 ){

                list_increment(matrix->lines[index_2], matrix->columns[c], index_2, c, *val_1);
                list_decrement(matrix->lines[index_1], matrix->columns[c], index_1, c);

                swap_confirm++;
                break;
                
            } else {
                list_iterator_next(li, 'c');
            }          
        }

        /* se a lista acabou antes de chegar ao índice 2, realiza o swap */
        if( val_1 && !swap_confirm ){
            list_increment(matrix->lines[index_2], matrix->columns[c], index_2, c, *val_1);
            list_decrement(matrix->lines[index_1], matrix->columns[c], index_1, c);
        }

        free(li);
    }

}

/*
Complexidade: O((L + C) + (L1*nL1)*(nL + nC)) = O(a + (L1*nL1)*i)
a =  complexidade de matrix_construct ( O(L + C) ); i = complexidade de list_increment ( O(nL + nC) );
L1 = número de linhas da matriz 1; nL1 = qtd máxima de nodes na linha L1; 
L = número de linhas da nova matriz; nL = qtd máxima de nodes na linha L; C = número de colunas da nova matriz; nC = qtd máxima de nodes na coluna C;

-> Cria uma nova matriz. Para cada linha da matriz base pertencente ao intervalo dado (no pior caso, percorre todas as linhas), 
itera sobre seus nodes e os incrementa na nova matriz.
*/
Matrix *matrix_slice(Matrix *matrix, int *qty_matrices, int start_line, int start_column, int end_line, int end_column, char hide_print){

    hide_print == 0 ? printf("\n===============|MATRIX SLICE|===============\n") : 1;

    /* Calcula a qty de linhas e colunas da nova matriz */
    int qty_lines = end_line - start_line + 1;
    int qty_columns = end_column - start_column + 1;

    Matrix *new_matrix = matrix_construct(qty_matrices, qty_lines, qty_columns, hide_print);

    /* Itera sobre cada linha do intervalo dado */
    /* Se uma linha for negativa (no caso da convolução), não realiza nenhuma operação */
    for( int l = start_line; l <= end_line; l++ ){

        if( l >= 0 && l < matrix->number_lines ){
            ListIterator *li = list_front_iterator(matrix->lines[l]);

            while( !list_iterator_is_over(li) ){
                int c = list_iterator_return_place(li, 'c');
                data_type val = *list_iterator_next(li, 'l');

                /* Verifica se a coluna está no intervalo dado e calcula as posições para a nova matriz */
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

/*
Complexidade: O((L + C) + (L1*nL1)*(nL + nC)) = O(a + (L1*nL1)*i)
a =  complexidade de matrix_construct ( O(L + C) ); i = complexidade de list_increment ( O(nL + nC) );

L1 = número de linhas da matriz 1; nL1 = qtd máxima de nodes na linha L1; 
L = número de linhas da nova matriz; nL = qtd máxima de nodes na linha L; C = número de colunas da nova matriz; nC = qtd máxima de nodes na coluna C;

-> Cria uma nova matriz. Para cada linha da matriz base, itera sobre seus nodes e os incrementa na nova matriz.
*/
Matrix *matrix_transposed(Matrix *matrix, int *qty_matrices){

    printf("\n============|TRANSPOSED MATRIX|============\n");

    int qty_lines = matrix->number_columns;
    int qty_columns = matrix->number_lines;

    Matrix *new_matrix = matrix_construct(qty_matrices, qty_lines, qty_columns, 0);

    /* Itera sobre cada linha e incrementa a nova matrix 
    -> linha 2 da matriz 1 equivale a coluna 2 da matriz 2 */
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

/*
Complexidade: O(a + L*C(s + p + u + v + 2d))
a =  complexidade de matrix_construct ( O(L + C) ); s = complexidade de matrix_slice ( O(a + (L1*nL1)*i) );
p = complexidade de multiply_point_to_point ( O(a + (L1*nL1 + L2*nL2)*i) ); u = complexidade de add_all_values ( O(Li*nLi) )
v = complexidade de matrix_assign_value ( O(2nL + nC) ); d = complexidade de matrix_destroy ( O(Li*nLi + Ci) );

L = número de linhas da nova matriz; nL = qtd máxima de nodes na linha L; C = número de colunas da nova matriz; nC = qtd máxima de nodes na coluna C;
L1 = número de linhas da matriz 1; nL1 = qtd máxima de nodes na linha L1; L2 = número de linhas da matriz 2; nL2 = qtd máxima de nodes na linha L2;
Li = número de linhas da matriz de suporte; nLi = qtd máxima de nodes na linha Li; Ci = número de colunas da matriz de suporte;

-> Cria uma nova matriz. Para cada célula da matriz base: cria uma matriz1 por slice; a multiplicacao da matriz1 pelo kernel cria a matriz2; 
soma-se todos os valores da matriz2 e atribui esse valor à nova matriz; destrói as matrizes 1 e 2.
*/
Matrix *matrix_convolution(Matrix *matrix, Matrix *kernel, int *qty_matrices){
    Matrix *support_1 = NULL, *support_2 = NULL;
    int *qty_supports = (int*) malloc( sizeof(int) );

    printf("\n===============|CONVOLUTION|===============\n");

    /* Calcula a quantidade de linhas da célula central até a borda */
    int edge_kernel = kernel->number_lines/2;

    Matrix *new_matrix = matrix_construct(qty_matrices, matrix->number_lines, matrix->number_columns, 0);

    for( int l = 0; l < matrix->number_lines; l++ ){
        for( int c = 0; c < matrix->number_columns; c++ ){
            (*qty_supports) = 0;

            /* Retorna a submatriz de mesmo tamanho que o kernel */
            support_1 = matrix_slice(matrix, qty_supports, l-edge_kernel, c-edge_kernel, l+edge_kernel, c+edge_kernel, '1');

            /* Retorna a matriz resultante da multiplicacao ponto a ponto da submatriz e do kernel */
            support_2 = multiply_point_to_point(support_1, kernel, qty_supports, '1');

            /* Soma todos os valores da matriz 2 */
            data_type new_value = add_all_values(support_2);

            /* Atribui a soma como uma célula da nova matriz */
            matrix_assign_value(new_matrix, l, c, new_value);

            matrix_destroy(support_1);          
            matrix_destroy(support_2);          
        }
    }
    free(qty_supports);

    return new_matrix;
}

/*
Complexidade: O(L*nL)
L = número de linhas; nL = qtd máxima de nodes em uma linha;

-> Percorre cada node de cada linha.
*/
data_type add_all_values(Matrix *matrix){
    ListIterator *li = NULL;
    data_type sum = 0;

    /* Soma todos os valores de uma matriz */
    for( int l = 0; l < matrix->number_lines; l++ ){
        li = list_front_iterator(matrix->lines[l]);

        while( !list_iterator_is_over(li) ){
            sum += *list_iterator_next(li, 'l');
        }
        free(li);
    }

    return sum;
}

/*
Complexidade: O(L*nL)
L = número de linhas; nL = qtd máxima de nodes em uma linha;

-> Percorre cada node de cada linha.
*/
void print_dense_matrix(Matrix *matrix){
    ListIterator *li = NULL;
    data_type value = 0;

    printf(":dense matrix:\n");

    /* Para cada linha, se tiver um node numa posição -> imprimir o seu valor
    do contrário -> imprimir 0 */
    for( int l = 0; l < matrix->number_lines; l++ ){
        li = list_front_iterator(matrix->lines[l]);

        for( int c = 0; c < matrix->number_columns; c++ ){

            value = ( !list_iterator_is_over(li) && list_iterator_return_place(li, 'c') == c ) ? 
            (*list_iterator_next(li, 'l')) : 0;
 
            printf("%.1f ", value);
        }
        free(li);
        printf("\n");
    }
    printf("\n");

    // 
}

/*
Complexidade: O(L*nL)
L = número de linhas; nL = qtd máxima de nodes em uma linha;

-> Percorre cada node de cada linha.
*/
void print_sparse_matrix(Matrix *matrix){
    ListIterator *li = NULL;
    data_type value = 0;
    int c = 0;

    printf("\n:sparse matrix:\n");

    /* Itera sobre cada linha e imprime os valores presentes cada node */
    for( int l = 0; l < matrix->number_lines; l++ ){
        li = list_front_iterator(matrix->lines[l]);

        while( !list_iterator_is_over(li) ){
            c = list_iterator_return_place(li, 'c');
            value = *list_iterator_next(li, 'l');

            printf("%.1f (%dx%d)  ", value, l, c);
        }            
        free(li);
        printf("\n");
    }
    printf("\n");
}

/*
Complexidade: O(L*nL)
L = número de linhas; nL = qtd máxima de nodes em uma linha;

-> Percorre cada node de cada linha e salva seus dados em um arquivo binário.
*/
void save_binary_matrix(Matrix *matrix, int index){
    char path[11] = PATH_FILE;
    FILE *arq = fopen(path, "wb");

    printf("\n===============|SAVE MATRIX|===============\n");

    if( !arq ){
        printf("ERROR: couldn't open the file!\n");
        exit(1);
    }
    printf("File open!");  


    fwrite( &matrix->number_lines, sizeof(int), 1, arq);
    fwrite( &matrix->number_columns, sizeof(int), 1, arq);

    for( int i = 0; i < matrix->number_lines; i++ )
        save_binary_list(arq, matrix->lines[i]);
    
    printf("\nThe matrix '%d' was saved in the file '%s'!\n\n", index, PATH_FILE);    

    fclose(arq);
}

/*
Complexidade: O((L + C) + (L1*nL1)*(nL + nC)) = O(a + (L1*nL1)*i)
a =  complexidade de matrix_construct ( O(L + C) ); i = complexidade de list_increment ( O(nL + nC) );
L = número de linhas da nova matriz; nL = qtd máxima de nodes em uma linha L;
L1 = número de linhas da matriz 1; nL1 = qtd máxima de nodes na linha L1; 

-> Cria uma nova matriz. Para cada node de cada linha da nova matriz, lê seus dados e o incrementa na matriz.
*/
Matrix *read_binary_matrix(int *qty_matrices){
    char path[11] = PATH_FILE;
    FILE *arq = fopen(path, "rb");

    printf("\n===============|READ MATRIX|===============\n");

    if( !arq ){
        printf("ERROR: couldn't open the file!\n");
        exit(1);
    }
    printf("File open!");  


    int qty_lines = 0, qty_columns = 0;

    fread( &qty_lines, sizeof(int), 1, arq);
    fread( &qty_columns, sizeof(int), 1, arq);

    Matrix *new_matrix = matrix_construct(qty_matrices, qty_lines, qty_columns, 0);


    for( int i = 0; i < new_matrix->number_lines; i++ )
        read_binary_list(arq, new_matrix->lines, new_matrix->columns);

    fclose(arq);
    return new_matrix;
}
