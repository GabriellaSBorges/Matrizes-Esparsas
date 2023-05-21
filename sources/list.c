#include "../headers/list.h"

/* representa cada linha ou coluna */
struct List{
    Node *head;
    Node *last;
    int size;
};

struct ListIterator{
    Node *current;
};


/*
Complexidade: O(R)
R = número de listas; 
-> Percorre o conjunto de listas (linhas ou colunas), inicializando cada uma.
*/
List **list_construct(int qty_lists){

    List **list = (List **) malloc( qty_lists * sizeof(List*) );

    for( int i = 0; i < qty_lists; i++ ){
        list[i] = (List*) malloc( sizeof(List) );

        if( list[i] == NULL ){
            printf("ERROR: failure to alloc space for the list.\n\n");
            exit(1);
        } 

        list[i]->head = NULL;
        list[i]->last = NULL;
        list[i]->size = 0;
    }

    return list;
}

/*
Complexidade: O(L*nL)
L = número de linhas; nL = qtd máxima de nodes em uma linha; 
-> Percorre todas as linhas e destrói cada um de seus nodes.
*/
void list_destroy(List **list, int qty_lists, char list_type){
    ListIterator *li = NULL;

    for( int i = 0; i < qty_lists; i++ ){

        if( list_type == 'l' ){
            li = list_front_iterator(list[i]);

            while( !list_iterator_is_over(li) )
                list_iterator_node_destroy(li, list_type); 

            free(li);
        }             
        free(list[i]);
    }     
    
    free(list);  
}

/*
Complexidade: O(nL)
nL = qtd máxima de nodes em uma linha; 
-> Percorre todos os nodes de uma linha até achar o desejado.
*/
void list_decrement(List *line, List *column, int l, int c){

    Node *n = list_find_node(line, c, 'a', 'l', 'c');

    Node *next_line = node_return_next(n, 'l');
    Node *prev_line = node_return_prev(n, 'l');
    Node *next_column = node_return_next(n, 'c');
    Node *prev_column = node_return_prev(n, 'c');

    /* Ajusta a lista para que fique sem o node e o destrói */
    list_remove_node(line, next_line, prev_line, 'l');
    list_remove_node(column, next_column, prev_column, 'c');

    line->size--;
    column->size--;

    node_destroy(n);
}

/*
Complexidade: O(1)
*/
void list_remove_node(List *row, Node *next_node, Node *prev_node, char list_type){

    /* A lista possui um único node */
    if( row->size == 1 ){ // 
        row->last = row->head = NULL; 

    /* O node está no meio da lista */
    } else if( prev_node != NULL && next_node != NULL ) { 
        assign_prev_node(next_node, prev_node, list_type);
        assign_next_node(prev_node, next_node, list_type);

    /* O node está no início da lista */
    } else if( prev_node == NULL ) { 
        row->head = node_return_next(row->head, list_type);
        assign_prev_node(row->head, NULL, list_type);

    /* O node está no final da lista */
    } else if( next_node == NULL ) { 
        row->last = node_return_prev(row->last, list_type);
        assign_next_node(row->last, NULL, list_type);       
    } 
}

/*
Complexidade: O(nL + nC)
nL = qtd máxima de nodes em uma linha; nC = qtd máxima de nodes em uma coluna; 
-> Percorre todos os nodes de uma linha até achar o desejado (prev node), realiza o mesmo processo a coluna.
*/
void list_increment(List *line, List *column, int l, int c, data_type val){

    Node *prev_line = list_find_node(line, c, 'p', 'l', 'c');
    Node *next_line = ( line->size == 0 ) ? NULL : node_return_next(prev_line, 'l');
    
    Node *prev_column = list_find_node(column, l, 'p', 'c', 'l');
    Node *next_column = ( column->size == 0 ) ? NULL : node_return_next(prev_column, 'c');

    Node *n = node_construct(val, l, c, next_line, prev_line, next_column, prev_column);
    
    /* Após construir o novo node, liga ele à linha e à coluna */
    list_insert_node(line, n, next_line, prev_line, 'l');
    list_insert_node(column, n, next_column, prev_column, 'c');

    line->size++;
    column->size++;
}

/*
Complexidade: O(1)
*/
void list_insert_node(List *row, Node *new_node, Node *next_node, Node *prev_node, char list_type){

    /* O node é o primeiro a ser incluído */
    if( row->head == NULL ) {
        row->last = row->head = new_node; 

    /* Entrará no meio da lista */
    } else if( prev_node != NULL && next_node != NULL ){ 
        assign_prev_node(next_node, new_node, list_type);
        assign_next_node(prev_node, new_node, list_type);

    /* Entrará no início da lista */
    } else if( prev_node == NULL ) { 
        assign_prev_node(row->head, new_node, list_type);
        row->head = new_node;

    /* Entrará no final da lista */
    } else if( next_node == NULL ) { 
        assign_next_node(row->last, new_node, list_type);
        row->last = new_node;
    } 
}

/*
Complexidade: O(nL)
nL = qtd máxima de nodes em uma linha;
-> Percorre todos os nodes de uma linha até achar o desejado.
*/
Node *list_find_node(List *row, int index, char node_type, char list_type, char position_type){
    ListIterator *li = list_front_iterator(row);
    Node *n = NULL;

    if( list_iterator_is_over(li) ){
        free(li);
        return n;
    }
        
    switch(node_type){
        /* prev node */
        case 'p':                
            /* Acha o último node da lista ou o anterior ao índice desejado */
            while( node_return_next(li->current, list_type) && index > node_return_place(li->current, position_type)+1 )
                li->current = node_return_next(li->current, list_type); 

            n = li->current;
            break;


        /* next node */
        case 'n':     
            /* Acha o primeiro node após o índice desejado */
            while( !list_iterator_is_over(li) && index > node_return_place(li->current, position_type)-1 )
                li->current = node_return_next(li->current, list_type);
     
            n = li->current;
            break;


        /* actual node */
        case 'a':
            /* Acha o node de índice desejado */
            while( !list_iterator_is_over(li) && node_return_place(li->current, position_type) != index )
                li->current = node_return_next(li->current, list_type);

            n = li->current;
            break;  
    }
    
    free(li);
    return n;
}



/* FUNCTIONS LIST ITERATOR */

/*
Complexidade: O(1)
*/
int list_iterator_is_over(ListIterator *li){
    return ( !li->current ) ? 1 : 0;
}

/*
Complexidade: O(1)
*/
ListIterator *list_front_iterator(List *l){
    ListIterator *li = malloc( 1 * sizeof(ListIterator) );
    li->current = l->head;

    return li;
}

/*
Complexidade: O(1)
*/
data_type *list_iterator_next(ListIterator *li, char list_type){
    data_type *n = node_return_value(li->current);

    li->current = (!li->current) ? NULL : node_return_next(li->current, list_type);
    return n;
}

/*
Complexidade: O(1)
*/
int list_iterator_return_place(ListIterator *li, int position_type){
    return node_return_place(li->current, position_type);
}

/*
Complexidade: O(1)
*/
void list_iterator_node_destroy(ListIterator *li, char list_type){
    Node *n = li->current;

    li->current = node_return_next(n, list_type);
    node_destroy(n);
}



/* BINARY FILE */

/*
Complexidade: O(nL)
nL = qtd máxima de nodes em uma linha;

-> Percorre cada node de uma linha e salva seus dados em um arquivo binário.
*/
void save_binary_list(FILE *arq, List *row){
    data_type *val = 0;
    int l = 0, c = 0;

    fwrite( &row->size, sizeof(int), 1, arq);
    
    ListIterator *li = list_front_iterator(row);

    /* Salva os dados de cada node */
    while( !list_iterator_is_over(li) ){
        l = node_return_place(li->current, 'l');
        c = node_return_place(li->current, 'c');

        val = list_iterator_next(li, 'l');

        fwrite( &l, sizeof(int), 1, arq);
        fwrite( &c, sizeof(int), 1, arq);
        fwrite( val, sizeof(data_type), 1, arq);
    }

    free(li);
}

/*
Complexidade: O(nL*(nL + nC)) = O(nL*i)
nL = qtd máxima de nodes em uma linha; nC = qtd máxima de nodes em uma coluna;
i = complexidade de list_increment ( O(nL + nC) );

-> Para cada node de uma linha, lê seus dados e o incrementa.
*/
void read_binary_list(FILE *arq, List **lines, List **columns){
    data_type val = 0;
    int size = 0, l = 0, c = 0;

    fread( &size, sizeof(int), 1, arq );

    /* Lê os dados de cada node */
    for( int i = 0; i < size; i++ ){
        fread( &l, sizeof(int), 1, arq);
        fread( &c, sizeof(int), 1, arq);
        fread( &val, sizeof(data_type), 1, arq);

        list_increment(lines[l], columns[c], l, c, val);
    }
}

