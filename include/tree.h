#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <locale.h>
#include <conio.h>
#include <graphviz/cgraph.h>

#include "..\library\errors.h"

#define SPEC "%s"

typedef char* elem_t;
const elem_t POISON = '\0';

const int DATA_SIZE = 17;

struct node_tree
{
    elem_t data;
    struct node_tree* left;
    struct node_tree* right;
};

void tree_print (struct node_tree* node);

int node_insert (struct node_tree* node);

void tree_dtor (struct node_tree* node);

struct node_tree* tree_search (struct node_tree* node, elem_t elem);

void clean_buffer ();

void save_graphviz (Agraph_t *graph, const char* filename);

void build_graphviz(struct node_tree* root, Agraph_t* graph);

#endif // TREE_H_INCLUDED
