#include "list.h"

/* representa cada linha ou coluna */
struct List{
    Node_pt head;
    Node_pt last;
    int size;
};

struct ListIterator{
    Node_pt current;
};


List_pt *list_construct(List_pt *list, int qty_lists){

    list = (List_pt*) malloc( qty_lists * sizeof(List_pt) );

    if( list == NULL ){
        printf("ERROR: failure to alloc space for the list.\n\n");
        exit(1);
    } 

    for( int i = 0; i < qty_lists; i++ ){

        list[i] = (List_pt) malloc( sizeof(List) );

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

void list_destroy(List_pt *list, int qty_lists, char list_type){
    ListIterator_pt li = NULL;
    int c = 0;

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

int verify_position_occupied(List_pt row, int p_searched, char position_type){
    ListIterator_pt li = list_front_iterator(row);
    int p = 0;

    if( row->head != NULL ){
        printf("VAL %f \n", node_return_value(row->head));
        // printf("L %d C %d\n", node_return_place(row->head, 'l'), node_return_place(row->head, 'c'));
    }

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
void list_assign_value(List_pt row, int p_searched, data_type val, char position_type){
    ListIterator_pt li = list_front_iterator(row);
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

void list_decrement(List_pt line, List_pt column, int l, int c){

    Node_pt next_line = find_node_row(line, c, 'n', 'l', 'c');
    Node_pt prev_line = find_node_row(line, c, 'p', 'l', 'c');
    Node_pt next_column = find_node_row(column, l, 'n', 'c', 'l');
    Node_pt prev_column = find_node_row(column, l, 'p', 'c', 'l');

    line->size--;
    column->size--;

    Node *n = find_node_row(line, c, 'a', 'l', 'c');

    list_remove_node(line, next_line, prev_line, 'l');
    list_remove_node(column, next_column, prev_column, 'c');

    node_destroy(n);
}

void list_remove_node(List_pt row, Node_pt next_node, Node_pt prev_node, char list_type){


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

void list_increment(List_pt line, List_pt column, int l, int c, data_type val){

    Node_pt next_line = find_node_row(line, c, 'n', 'l', 'c');
    Node_pt prev_line = find_node_row(line, c, 'p', 'l', 'c');
    Node_pt next_column = find_node_row(column, l, 'n', 'c', 'l');
    Node_pt prev_column = find_node_row(column, l, 'p', 'c', 'l');

    // if( next_line = NULL )
    //     printf("OI %f\n", node_return_value(next_line));
    // else 
    //     printf("NULL\n");

    Node *n = node_construct(val, l, c, next_line, prev_line, next_column, prev_column);

    line->size++;
    column->size++;
    
    list_insert_node(line, n, next_line, prev_line, 'l');
    list_insert_node(column, n, next_column, prev_column, 'c');

    // printf("VAL %f %f %f\n", node_return_value(n), node_return_value(line->head), node_return_value(column->head));
    // printf("L %d C %d\n", node_return_place(line->head, 'l'), node_return_place(line->head, 'c'));

}

Node_pt find_node_row(List_pt row, int index_searched, char node_type, char list_type, char position_type){
    ListIterator_pt li = list_front_iterator(row);
    Node_pt n = NULL;

    if( node_type == 'a' ){
        n = list_iterator_find_node(li, index_searched, node_type, list_type, position_type);

    } else if( row->head != NULL ) {
        int head_index = node_return_place(row->head, position_type);

        if( index_searched > head_index ){       
            n = list_iterator_find_node(li, index_searched, node_type, list_type, position_type);

        } else if( index_searched < head_index ) {
            if( node_type == 'n' )
                n = row->head;
        } 
    }   

    free(li);

    return n;
}

void list_insert_node(List_pt row, Node_pt new_node, Node_pt next_node, Node_pt prev_node, char list_type){
    
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


/* FUNCOES LIST ITERATOR */

int list_iterator_is_over(ListIterator_pt li){

    if( li->current == NULL )
        return 1;

    return 0;
}

ListIterator_pt list_front_iterator(List_pt l){
    ListIterator_pt it = malloc( 1 * sizeof(ListIterator) );

    it->current = l->head;

    return it;
}

// int list_iterator_next(ListIterator_pt li, char list_type, char position_type){
//     int p = -1;

//     li->current = node_return_next(li->current, list_type);

//     if( li->current != NULL )
//         p = node_return_place(li->current, position_type);


//     return p;
// }

Node_pt list_iterator_find_node(ListIterator_pt li, int index, char node_type, char list_type, char position_type){
    //aplicar o switch

    if( node_type == 'p'){ /* prev node */
        while( index > node_return_place(li->current, position_type)+1 )
            li->current = node_return_next(li->current, list_type);

        return li->current;
        

    } else if( node_type == 'n' ) { /* next node */
        while( index > node_return_place(li->current, position_type)-1 ){
            li->current = node_return_next(li->current, list_type);

            if( li->current == NULL )
                break;
            
        return li->current;
        }


    } else if( node_type == 'a' ) { /* actual node */
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

void list_iterator_node_destroy(ListIterator_pt li, char list_type){
    Node_pt n = li->current;

    li->current = node_return_next(n, list_type);
    node_destroy(n);
}


/* FUNCOES DE RETORNO */

data_type list_return_value(List_pt row, int p_searched, char position_type){
    ListIterator_pt li = list_front_iterator(row);
    data_type n;
    int p = 0;

    while( !list_iterator_is_over(li) ){
            p = node_return_place(li->current, position_type);

            if( p == p_searched ){
                n = node_return_value(li->current);
                free(li);
                printf("%.0f ", n);
                return n;
            } 

            li->current = node_return_next(li->current, position_type);
        }
    printf("0 ");
    free(li);
    return 0;
}

// data_type list_return_value(List_pt row, int p_searched, char position_type){
//     ListIterator_pt li = list_front_iterator(row);
//     data_type n;
//     int p = 0;

//     while( !list_iterator_is_over(li) ){
//             p = node_return_place(li->current, position_type);

//             if( p == p_searched ){
//                 n = node_return_value(li->current);
//                 free(li);
//                 printf("%.0f ", n);
//                 return n;
//             } 

//             li->current = node_return_next(li->current, position_type);
//         }
//     printf("0 ");
//     free(li);
//     return 0;
// }