#ifndef _POSITION_H_
#define _POSITION_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Position Position;


Position *position_construct(Position *p, int l, int c);

void position_destroy(Position *p);

int position_return_line(Position *p);

int position_return_column(Position *p);


#endif