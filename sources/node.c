#include "../headers/node.h" 

struct Node{
    Position_pt place;
    data_type value;
    Node_pt next_line;
    Node_pt next_column;
    Node_pt prev_line;
    Node_pt prev_column;
};

Node_pt node_construct(data_type value, int l, int c, Node *next_line, Node *prev_line, Node *next_column, Node* prev_column){

    Node_pt n = (Node_pt) malloc( sizeof(Node) );

    n->place = position_construct(n->place, l, c);
    n->value = value;

    n->next_line = next_line;
    n->prev_line = prev_line;
    n->next_column = next_column;
    n->prev_column = prev_column;

    return n;
}

void node_destroy(Node_pt n){
    free(n->place);
    free(n);
}

void assign_value_prev_node(Node_pt node, Node_pt new_node, char list_type){

    if( list_type == 'l' )
        node->prev_line = new_node;
    if( list_type == 'c' )
        node->prev_column = new_node;

}

void assign_value_next_node(Node_pt node, Node_pt new_node, char list_type){

    if( list_type == 'l' )
        node->next_line = new_node;
    if( list_type == 'c' )
        node->next_column = new_node;

}

void node_assign_value(Node_pt n, data_type val){
    n->value = val;
}

data_type node_return_value(Node_pt n){
    return n->value;
}

Node_pt node_return_next(Node_pt n, char list_type){
    
    if( list_type == 'l' )
        return n->next_line;
    if( list_type == 'c' )
        return n->next_column;
}

Node_pt node_return_prev(Node_pt n, char list_type){
    
    if( list_type == 'l' )
        return n->prev_line;
    if( list_type == 'c' )
        return n->prev_column;
}

int node_return_place(Node_pt n, char position_type){

    if( position_type == 'l')
        return position_return_line(n->place);

    if( position_type == 'c' )
        return position_return_column(n->place);
}

// Node_pt node_return(Node_pt n){
//     return n;
// }