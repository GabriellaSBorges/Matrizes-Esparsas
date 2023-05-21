#include "../headers/position.h"

struct Position{
    int line; 
    int column; 
};


/*
Complexidade: O(1)
*/
Position *position_construct(int l, int c){

    Position *p = (Position*) malloc( sizeof(Position) );

    p->line = l;
    p->column = c;

    return p; 
}

/*
Complexidade: O(1)
*/
void position_destroy(Position *p){
    free(p);
}

/*
Complexidade: O(1)
*/
int position_return_line(Position *p){
    return p->line;
}

/*
Complexidade: O(1)
*/
int position_return_column(Position *p){
    return p->column;
}

