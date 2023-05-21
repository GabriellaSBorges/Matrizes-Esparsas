#ifndef _POSITION_H_
#define _POSITION_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Position Position;


/**
 * @brief Aloca memória para um ponteiro de Position e o inicializa
 * 
 * @param l Linha do node
 * @param c Coluna do node
 * @return Position* Ponteiro para Position
 */
Position *position_construct(int l, int c);

/**
 * @brief Libera memória de Position*
 * 
 * @param p Ponteiro para Position
 */
void position_destroy(Position *p);

/**
 * @brief Retorna a 'linha' de Position
 * 
 * @param p Ponteiro para Position
 * @return int Índice da linha
 */
int position_return_line(Position *p);

/**
 * @brief Retorna a 'coluna' de Position
 * 
 * @param p Ponteiro para Position
 * @return int Índice da coluna
 */
int position_return_column(Position *p);


#endif