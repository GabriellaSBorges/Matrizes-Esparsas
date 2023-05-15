#ifndef _NODE_H_
#define _NODE_H_

#include "position.h"

typedef float data_type;

typedef struct Node Node;
typedef Node* Node_pt;

Node_pt node_construct(data_type value, int l, int c, Node *next_line, Node *prev_line, Node *next_column, Node* prev_column);

void node_destroy(Node_pt n);

void assign_value_prev_node(Node_pt node, Node_pt new_node, char list_type);

void assign_value_next_node(Node_pt node, Node_pt new_node, char list_type);

void node_assign_value(Node_pt n, data_type val);

data_type node_return_value(Node_pt n);

Node_pt node_return_next(Node_pt n, char list_type);

Node_pt node_return_prev(Node_pt n, char list_type);

int node_return_place(Node_pt n, char position_type);

// Node_pt node_return(Node_pt n);

#endif