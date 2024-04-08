#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <locale.h>
#include <conio.h>

#include "..\library\errors.h"
#include "..\library\DSL.h"
#include "..\stack\include\stack.h"
#include "..\stack\include\stack_path.h"

#define SPEC "%s"

typedef char* elem_t;
typedef int   elem_t_path;

const elem_t POISON = '\0';

const int DATA_SIZE = 20;

enum POSITION
{
    LEFT  = 0,
    RIGHT = 1,
    ROOT  = 2,
};

struct node_tree
{
    elem_t            data;
    struct node_tree* left;
    struct node_tree* right;
    size_t            num_in_tree;
};

int run_akinator (struct node_tree* node, FILE* file_output);

int play_akinator (struct node_tree* node);

void tree_dtor (struct node_tree* node);

int node_search (struct node_tree* node, elem_t elem, struct stack_path* stk_path);

int give_node_information (elem_t element, struct node_tree* node);

int node_insert (struct node_tree* node, struct node_tree* root);

int add_description (struct node_tree* node);

void clean_buffer ();

int tree_output (FILE* file_output, struct node_tree* node);

int get_database (struct node_tree** root, char* file_input);

int construct_data_nodes (struct node_tree* root, char* text_data, size_t file_size);

size_t file_size_measure (FILE* const file_p);

int build_graphviz (struct node_tree* root);

int compare_two_nodes (struct node_tree* root);

int find_nodes_differences (int ptr, struct node_tree* node, size_t len_path_1, elem_t_path* path_1,
                                                             size_t len_path_2, elem_t_path* path_2);
#endif // TREE_H_INCLUDED
