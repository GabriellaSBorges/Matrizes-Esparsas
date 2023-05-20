#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_

#include "node.h"

typedef struct List List;
typedef struct ListIterator ListIterator;


List **list_construct(List **row, int size_row);

void list_destroy(List **list, int qty_lists, char list_type);

void list_decrement(List *line, List *column, int l, int c);

void list_remove_node(List *row, Node *next_node, Node *prev_node, char list_type);

void list_increment(List *line, List *column, int l, int c, data_type val);

void list_insert_node(List *row, Node *new_node, Node *next_node, Node *prev_node, char list_type);

Node *find_node_row(List *row, int index, char node_type, char list_type, char position_type);

Node *list_iterator_find_node(ListIterator *li, int index, char node_type, char list_type, char position_type);






int list_iterator_is_over(ListIterator *li);

ListIterator *list_front_iterator(List *l);

data_type *list_iterator_next(ListIterator *li, char position_type);

int list_iterator_return_place(ListIterator *li, int position_type);

// data_type *list_iterator_return_value(ListIterator *li);

void list_iterator_node_destroy(ListIterator *li, char list_type);






// int list_return_size(List *row);

void save_binary_list(FILE *arq, List *row);

void read_binary_list(FILE *arq, List **lines, List **columns, int index_line);


#endif 