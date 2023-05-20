#ifndef _NODE_H_
#define _NODE_H_

#include "position.h"

typedef float data_type;

typedef struct Node Node;
// typedef Node* Node_pt;

Node *node_construct(data_type value, int l, int c, Node *next_line, Node *prev_line, Node *next_column, Node* prev_column);

void node_destroy(Node *n);

void assign_value_prev_node(Node *node, Node *new_node, char list_type);

void assign_value_next_node(Node *node, Node *new_node, char list_type);

void node_assign_value(Node *n, data_type val);

data_type node_return_value(Node *n);

Node *node_return_next(Node *n, char list_type);

Node *node_return_prev(Node *n, char list_type);

int node_return_place(Node *n, char position_type);





#endif