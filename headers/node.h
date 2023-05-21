#ifndef _NODE_H_
#define _NODE_H_

#include "position.h"

typedef float data_type;
typedef struct Node Node;

/**
 * @brief Aloca memória para um node e o inicializa
 * 
 * @param value Valor do novo node
 * @param l Linha do novo node
 * @param c Coluna do novo node
 * @param next_line Next node na linha
 * @param prev_line Prev node na linha
 * @param next_column Next node na coluna
 * @param prev_column Prev node na coluna
 * @return Node* Ponteiro para o node criado
 */
Node *node_construct(data_type value, int l, int c, Node *next_line, Node *prev_line, Node *next_column, Node* prev_column);

/**
 * @brief Libera a memória do node
 * 
 * @param n Node que será destruído
 */
void node_destroy(Node *n);

/**
 * @brief Atribui new_node como 'prev' de node
 * 
 * @param node Node desejado
 * @param new_node Node que será atribuído 
 * @param list_type Tipo da lista que será ajustada
 */
void assign_prev_node(Node *node, Node *new_node, char list_type);

/**
 * @brief Atribui new_node como 'next' de node
 * 
 * @param node Node desejado
 * @param new_node Node que será atribuído 
 * @param list_type Tipo da lista que será ajustada
 */
void assign_next_node(Node *node, Node *new_node, char list_type);

/**
 * @brief Atribui um valor a um node já alocado
 * 
 * @param n Node desejada
 * @param val Valor que será atribuído
 */
void node_assign_value(Node *n, data_type val);

/**
 * @brief Retorna o valor presente no node
 * 
 * @param n Node desejado
 * @return data_type* Valor do node
 */
data_type *node_return_value(Node *n);

/**
 * @brief Retorna o 'next node' de um node 
 * 
 * @param n Node desejado
 * @param list_type Tipo da lista desejada
 * @return Node* Ponteiro para o next node
 */
Node *node_return_next(Node *n, char list_type);

/**
 * @brief Retorna o 'prev node' de um node 
 * 
 * @param n Node desejado
 * @param list_type Tipo da lista desejada
 * @return Node* Ponteiro para o prev node
 */
Node *node_return_prev(Node *n, char list_type);

/**
 * @brief Retorna a posição do node
 * 
 * @param n Node desejado
 * @param position_type Tipo de posição procurada (linha ou coluna)
 * @return int Posição do node
 */
int node_return_place(Node *n, char position_type);



#endif