#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <locale.h>
#include <conio.h>
//#include <graphviz/cgraph.h>

#include "..\library\errors.h"
#include "..\library\DSL.h"
#include "..\stack\include\stack.h"

#define SPEC "%s"

typedef char* elem_t;
const elem_t POISON = '\0';

const int DATA_SIZE = 17;

enum Position
{
    LEFT  = 0,
    RIGHT = 1
};

struct node_tree
{
    elem_t data;
    struct node_tree* left;
    struct node_tree* right;
    size_t            num_in_tree;
};

int run_acinator (struct node_tree* node);

void tree_dtor (struct node_tree* node);

int node_search (struct node_tree* node, elem_t elem);

int node_insert (struct node_tree* node, struct node_tree* root);

int add_discription (struct node_tree* node);

void clean_buffer ();

int tree_output (FILE* file_output, struct node_tree* node);

int get_database (struct node_tree*, char* file_input);

int construct_data_nodes (struct node_tree* root, char* text_data, size_t file_size);

size_t file_size_measure (FILE* const file_p);

int build_graphviz (struct node_tree* root);

void add_node_in_graph_1 (struct node_tree* node, FILE* file_graph, size_t* node_num);

void add_node_in_graph_2 (struct node_tree* node, FILE* file_graph);

//void save_graphviz (Agraph_t *graph, const char* filename);

//void build_graphviz(struct node_tree* root, Agraph_t* graph);

#endif // TREE_H_INCLUDED
