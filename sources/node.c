#include "../headers/node.h" 

struct Node{
    Position *place;
    data_type value;
    Node *next_line; // next in line
    Node *next_column;
    Node *prev_line;
    Node *prev_column;
};

Node *node_construct(data_type value, int l, int c, Node *next_line, Node *prev_line, Node *next_column, Node *prev_column){

    Node *n = (Node*) malloc( sizeof(Node) );

    n->place = position_construct(n->place, l, c);
    n->value = value;

    n->next_line = next_line;
    n->prev_line = prev_line;
    n->next_column = next_column;
    n->prev_column = prev_column;

    return n;
}

void node_destroy(Node *n){
    free(n->place);
    free(n);
}

void assign_prev_node(Node *node, Node *new_node, char list_type){

    if( list_type == 'l' )
        node->prev_line = new_node;
    if( list_type == 'c' )
        node->prev_column = new_node;

}

void assign_next_node(Node *node, Node *new_node, char list_type){

    if( list_type == 'l' )
        node->next_line = new_node;
    if( list_type == 'c' )
        node->next_column = new_node;

}

void node_assign_value(Node *n, data_type val){
    n->value = val;
}

data_type *node_return_value(Node *n){
    data_type *val = &n->value;

    return val;
}

Node *node_return_next(Node *n, char list_type){
    
    if( list_type == 'l' )
        return n->next_line;
    if( list_type == 'c' )
        return n->next_column;

    return NULL;
}

Node *node_return_prev(Node *n, char list_type){
    
    if( list_type == 'l' )
        return n->prev_line;
    if( list_type == 'c' )
        return n->prev_column;
    
    return NULL;
}

int node_return_place(Node *n, char position_type){

    if( position_type == 'l')
        return position_return_line(n->place);

    if( position_type == 'c' )
        return position_return_column(n->place);
    
    return -1;
}

