#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_

#include "node.h"

typedef struct List List;
typedef struct ListIterator ListIterator;


/**
 * @brief Aloca espaço para um ponteiro de listas duplamente encadeadas e as inicializa 
 * ( conjunto de linhas ou colunas de uma matriz )
 * 
 * @param qty_lists Número de listas que serão alocadas
 * @return List** Ponteiro de listas 
 */
List **list_construct(int qty_lists);

/**
 * @brief Destrói um ponteiro de listas (conjunto de linhas ou colunas)
 * 
 * @param list Ponteiro que terá memória liberada
 * @param qty_lists Quantidade de listas que serão liberadas
 * @param list_type Tipo da lista que será liberada (linha ou coluna)
 */
void list_destroy(List **list, int qty_lists, char list_type);

/**
 * @brief Remove um node da matriz e o destrói
 * 
 * @param line Ponteiro da linha onde o node está
 * @param column Ponteiro da coluna onde o node está
 * @param l Índice da linha desejada na matriz
 * @param c Índice da coluna desejada na matriz
 */
void list_decrement(List *line, List *column, int l, int c);

/**
 * @brief Liga os nodes laterais do node que será removido entre si
 * 
 * @param row Ponteiro para a lista que será ajustada
 * @param next_node Next node do node desejado
 * @param prev_node Prev node do node desejado
 * @param list_type Tipo da lista que será ajustada
 */
void list_remove_node(List *row, Node *next_node, Node *prev_node, char list_type);

/**
 * @brief Adiciona um novo node na matriz
 * 
 * @param line Ponteiro da linha onde o node estará
 * @param column Ponteiro da coluna onde o node estará
 * @param l Índice da linha desejada na matriz
 * @param c Índice da coluna desejada na matriz
 * @param val Valor do novo node
 */
void list_increment(List *line, List *column, int l, int c, data_type val);

/**
 * @brief Liga os nodes laterais (prev e next) ao novo node
 * 
 * @param row Ponteiro para a lista que será ajustada
 * @param new_node Novo node
 * @param next_node Next node do node criado
 * @param prev_node Prev node do node criado
 * @param list_type Tipo da lista que será ajustada
 */
void list_insert_node(List *row, Node *new_node, Node *next_node, Node *prev_node, char list_type);

/**
 * @brief Retorna o node procurado, seu next ou seu prev
 * 
 * @param row Ponteiro para a lista do node procurado
 * @param index índice do node procurado
 * @note Se a lista for uma linha, índice será de uma coluna; se a lista for uma coluna, índice será de uma linha
 * 
 * @param node_type Tipo de node procurado (actual, prev ou next)
 * @param list_type Tipo da lista que está sendo iterada (linha ou coluna)
 * @param position_type Tipo de índice do node (linha ou coluna)
 * @return Node* Nodo procurado
 */
Node *list_find_node(List *row, int index, char node_type, char list_type, char position_type);

/**
 * @brief Verifica se a lista iterada chegou ao fim
 * 
 * @param li Ponteiro para o iterador
 * @return int Retorna 1 se a lista terminou
 */
int list_iterator_is_over(ListIterator *li);

/**
 * @brief Retorna um iterador para o primeiro node da lista duplamente encadeada
 * 
 * @param l Lista desejada
 * @return ListIterator* Ponteiro para o iterador
 */
ListIterator *list_front_iterator(List *l);

/**
 * @brief Retorna o valor de um node e atualiza o iterador para o próximo node
 * 
 * @param li Ponteiro para o iterador
 * @param list_type Tipo da lista que está sendo iterada 
 * @return data_type* Ponteiro para o valor armazenado no node
 */
data_type *list_iterator_next(ListIterator *li, char list_type);

/**
 * @brief Retorna a posição (linha ou coluna) do node o qual o iterador aponta
 * 
 * @param li Ponteiro para o iterador
 * @param position_type Tipo de posição procurada
 * @return int Posição do node (linha ou coluna)
 */
int list_iterator_return_place(ListIterator *li, int position_type);

/**
 * @brief Atualiza o iterador para o próximo node e destrói o anterior
 * 
 * @param li Ponteiro para o iterador
 * @param list_type Tipo da lista que está sendo iterada 
 */
void list_iterator_node_destroy(ListIterator *li, char list_type);

/**
 * @brief Salva uma lista em um arquivo binário
 * 
 * @param arq Arquivo em que será salvada
 * @param row Lista que será salvada
 */
void save_binary_list(FILE *arq, List *row);

/**
 * @brief Lê uma lista de um arquivo binário, aloca e incrementa seus nodes
 * 
 * @param arq Arquivo lido
 * @param lines Ponteiro para o conjunto de linhas da matriz
 * @param columns Ponteiro para o conjunto de colunas da matriz
 */
void read_binary_list(FILE *arq, List **lines, List **columns);


#endif 