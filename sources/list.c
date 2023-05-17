#include "../headers/list.h"

/* representa cada linha ou coluna */
struct List{
    Node *head;
    Node *last;
    int size;
};

struct ListIterator{
    Node_pt current;
};


List **list_construct(List **list, int qty_lists){

    list = (List **) malloc( qty_lists * sizeof(List*) );

    if( list == NULL ){
        printf("ERROR: failure to alloc space for the list.\n\n");
        exit(1);
    } 

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

int verify_position_occupied(List *row, int p_searched, char position_type){
    ListIterator *li = list_front_iterator(row);
    int p = 0;

    while( !list_iterator_is_over(li) ){
        p = node_return_place(li->current, position_type);

        if( p == p_searched ){
            free(li);
            return 1;
        }       
        
        li->current = node_return_next(li->current, position_type);   
    }

    free(li);

    return 0;
}

// pode mesclar com a find row
void list_assign_value(List *row, int p_searched, data_type val, char position_type){
    ListIterator *li = list_front_iterator(row);
    int p = 0;

    while( !list_iterator_is_over(li) ){
        p = node_return_place(li->current, position_type);

        if( p == p_searched ){
            node_assign_value(li->current, val);
            break;
        }         
    }

    free(li); 
}

void list_decrement(List *line, List *column, int l, int c){

    Node *next_line = find_node_row(line, c, 'n', 'l', 'c');
    Node *prev_line = find_node_row(line, c, 'p', 'l', 'c');
    Node *next_column = find_node_row(column, l, 'n', 'c', 'l');
    Node *prev_column = find_node_row(column, l, 'p', 'c', 'l');

    line->size--;
    column->size--;

    Node *n = find_node_row(line, c, 'a', 'l', 'c');

    list_remove_node(line, next_line, prev_line, 'l');
    list_remove_node(column, next_column, prev_column, 'c');

    node_destroy(n);
}

void list_remove_node(List *row, Node *next_node, Node *prev_node, char list_type){

    if( row->size == 1 ){ // a lista ficara vazia
        row->last = row->head = NULL; 

    } else if( prev_node != NULL && next_node != NULL ) { // esta no meio da lista
        assign_value_prev_node(next_node, prev_node, list_type);
        assign_value_next_node(prev_node, next_node, list_type);

    } else if( prev_node == NULL ) { // esta no inicio da lista
        row->head = node_return_next(row->head, list_type);

        if( row->head != NULL )
            assign_value_prev_node(row->head, NULL, list_type);

    } else if( next_node == NULL ) { // esta no final da lista
        row->last = node_return_prev(row->last, list_type);

        if( row->last != NULL )
            assign_value_next_node(row->last, NULL, list_type);
    } 
}

void list_increment(List *line, List *column, int l, int c, data_type val){

    Node *next_line = find_node_row(line, c, 'n', 'l', 'c');
    Node *prev_line = find_node_row(line, c, 'p', 'l', 'c');
    Node *next_column = find_node_row(column, l, 'n', 'c', 'l');
    Node *prev_column = find_node_row(column, l, 'p', 'c', 'l');

    // if( next_line != NULL )
    //     printf("%d ", node_return_place(next_line, 'c'));
    // else 
    //     printf("NL ");
    // if( next_column != NULL )
    //     printf("%d ", node_return_place(next_column, 'l'));
    // else 
    //     printf("NC ");
    // if( prev_line != NULL )
    //     printf("%d ", node_return_place(prev_line, 'c'));
    // else 
    //     printf("PL ");
    //  if( prev_column != NULL )
    //     printf("%d ", node_return_place(prev_column, 'c'));
    // else 
    //     printf("PC ");

    Node *n = node_construct(val, l, c, next_line, prev_line, next_column, prev_column);

    line->size++;
    column->size++;
    
    list_insert_node(line, n, next_line, prev_line, 'l');
    list_insert_node(column, n, next_column, prev_column, 'c');
}

Node *find_node_row(List *row, int index_searched, char node_type, char list_type, char position_type){
    ListIterator *li = list_front_iterator(row);
    Node *n = NULL;

    if( node_type == 'a' ){
        n = list_iterator_find_node(li, index_searched, node_type, list_type, position_type);

    } else if( row->head != NULL ) {
        int head_index = node_return_place(row->head, position_type);

        if( index_searched > head_index ){       
            n = list_iterator_find_node(li, index_searched, node_type, list_type, position_type);

        } else {
            if( node_type == 'n' )
                n = row->head;
        } 
    }   
    free(li);

    return n;
}

void list_insert_node(List *row, Node *new_node, Node *next_node, Node *prev_node, char list_type){
    
    if( row->head == NULL ) { // a lista estava vazia
        row->last = row->head = new_node; 

    } else if( prev_node != NULL && next_node != NULL ){ // entrara no meio da lista
        assign_value_prev_node(next_node, new_node, list_type);
        assign_value_next_node(prev_node, new_node, list_type);

    } else if( prev_node == NULL ) { // esta no inicio da lista
        assign_value_prev_node(row->head, new_node, list_type);
        row->head = new_node;

    } else if( next_node == NULL ) { // esta no final da lista
        assign_value_next_node(row->last, new_node, list_type);
        row->last = new_node;
    } 

}


/* FUNCTIONS LIST ITERATOR */

int list_iterator_is_over(ListIterator *li){

    if( li->current == NULL )
        return 1;

    return 0;
}

ListIterator *list_front_iterator(List *l){
    ListIterator *li = malloc( 1 * sizeof(ListIterator) );
    li->current = l->head;

    return li;
}

Node *list_iterator_find_node(ListIterator *li, int index, char node_type, char list_type, char position_type){

    switch(node_type){

        /* prev node */
        case 'p':
            while( index > node_return_place(li->current, position_type)+1 )
                li->current = node_return_next(li->current, list_type);

            return li->current;

        /* next node */
        case 'n':
            while( index > node_return_place(li->current, position_type)-1 ){
                li->current = node_return_next(li->current, list_type);

                if( li->current == NULL )
                    break;
            }       
            return li->current;

        /* actual node */
        case 'a':
            int p = 0;

            while( !list_iterator_is_over(li) ){
                p = node_return_place(li->current, position_type);

                if( p == index )
                    return li->current;

                li->current = node_return_next(li->current, list_type);
            }
            
    }

    return NULL;
}

void list_iterator_node_destroy(ListIterator *li, char list_type){
    Node *n = li->current;

    li->current = node_return_next(n, list_type);
    node_destroy(n);
}

int list_iterator_return_place(ListIterator *li, int position_type){
    if( li->current == NULL) // é necessário?
        return -1;

    if( position_type == 'l')
        return node_return_place(li->current, 'l');
    if( position_type == 'c')
        return node_return_place(li->current, 'c');

}

data_type *list_iterator_next(ListIterator *li, char list_type){
    
    // data_type *n = NULL;
    data_type *n = node_return_value(li->current);
    li->current = node_return_next(li->current, list_type);

    return n;
}

/* FUNCOES DE RETORNO */

int list_return_size(List *row){
    return row->size;
}

