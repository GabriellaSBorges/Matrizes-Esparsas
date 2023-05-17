#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_

#include "node.h"

typedef struct List List;
typedef List* List_pt;

typedef struct ListIterator ListIterator;
typedef ListIterator* ListIterator_pt;


List **list_construct(List **row, int size_row);

void list_destroy(List **list, int qty_lists, char list_type);

int verify_position_occupied(List *row, int p_searched, char position_type);

void list_assign_value(List *row, int p_searched, data_type val, char position_type);

void list_decrement(List *line, List *column, int l, int c);

void list_remove_node(List *row, Node *next_node, Node *prev_node, char list_type);

void list_increment(List *line, List *column, int l, int c, data_type val);

Node *find_node_row(List *row, int index, char node_type, char list_type, char position_type);

void list_insert_node(List *row, Node *new_node, Node *next_node, Node *prev_node, char list_type);




int list_iterator_is_over(ListIterator *li);

ListIterator *list_front_iterator(List *l);

Node *list_iterator_find_node(ListIterator *li, int index, char node_type, char list_type, char position_type);

void list_iterator_node_destroy(ListIterator *li, char list_type);

int list_iterator_return_place(ListIterator *li, int position_type);




data_type *list_iterator_next(ListIterator *li, char position_type);

int list_return_size(List *row);

List **read_binary_list(FILE *arq, int number_lists);

#endif 