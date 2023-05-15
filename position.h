#ifndef _POSITION_H_
#define _POSITION_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Position Position;
typedef Position* Position_pt;


Position_pt position_construct(Position_pt p, int l, int c);

void position_destroy(Position_pt p);

int position_return_line(Position_pt p);

int position_return_column(Position_pt p);

#endif