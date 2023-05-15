#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_

#include "node.h"

typedef struct List List;
typedef List* List_pt;

typedef struct ListIterator ListIterator;
typedef ListIterator* ListIterator_pt;


List_pt *list_construct(List_pt *row, int size_row);

void list_destroy(List_pt *list, int qty_lists, char list_type);

int verify_position_occupied(List_pt row, int p_searched, char position_type);

void list_assign_value(List_pt row, int p_searched, data_type val, char position_type);

void list_decrement(List_pt line, List_pt column, int l, int c);

void list_remove_node(List_pt row, Node_pt next_node, Node_pt prev_node, char list_type);

void list_increment(List_pt line, List_pt column, int l, int c, data_type val);

Node_pt find_node_row(List_pt row, int index, char node_type, char list_type, char position_type);

void list_insert_node(List_pt row, Node_pt new_node, Node_pt next_node, Node_pt prev_node, char list_type);




int list_iterator_is_over(ListIterator *li);

ListIterator *list_front_iterator(List_pt l);

int list_iterator_next(ListIterator_pt li, char list_type, char position_type);

Node_pt list_iterator_find_node(ListIterator_pt li, int index, char node_type, char list_type, char position_type);

void list_iterator_node_destroy(ListIterator_pt li, char list_type);

Node_pt list_iterator_return_current(ListIterator_pt li, int position_type);




data_type list_return_value(ListIterator_pt li, int p_searched, char list_type);

int list_return_size(List_pt row);

#endif 