#include "../headers/position.h"

struct Position{
    int line; 
    int column; 
};

Position *position_construct(Position *p, int l, int c){

    p = (Position*) malloc( sizeof(Position) );

    p->line = l;
    p->column = c;

    return p; 
}

void position_destroy(Position *p){
    free(p);
}

int position_return_line(Position *p){
    return p->line;
}

int position_return_column(Position *p){
    return p->column;
}


