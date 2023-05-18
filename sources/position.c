#include "../headers/position.h"

struct Position{
    int line; 
    int column; 
};

Position_pt position_construct(Position_pt p, int l, int c){

    p = (Position_pt) malloc( sizeof(Position) );

    p->line = l;
    p->column = c;

    return p; 
}

void position_destroy(Position_pt p){
    free(p);
}

int position_return_line(Position_pt p){
    return p->line;
}

int position_return_column(Position_pt p){
    return p->column;
}

// Node *read_binary_node(FILE *arq){

//     Node *node = (Node*) malloc( sizeof(Node) );

//     node->place = read_binary_position(arq);

//     fread( &node->value, sizeof(data_type), 1, arq);

//     fread( &node->next_line, sizeof(Node), 1, arq);
//     fread( &node->next_column, sizeof(Node), 1, arq);
//     fread( &node->prev_line, sizeof(Node), 1, arq);
//     fread( &node->prev_column, sizeof(Node), 1, arq);


// }

void save_binary_position(FILE *arq, Position *p){

    fwrite( &p->line, sizeof(int), 1, arq );
    fwrite( &p->column, sizeof(int), 1, arq );
}