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


