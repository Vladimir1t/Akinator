#include "..\include\tree.h"

int main(int argc, char* argv[])
{
    setlocale (LC_ALL, "Rus");
    FOPEN (file_output, "file_output.txt", "a")

    struct node_tree* tree = NULL;                             // make a root of the tree
    CALLOC (tree, struct node_tree, 1)
    CALLOC (tree->data, char, DATA_SIZE)

    if (argc == 2 && get_database (tree, argv[1]) != SUCCESS)  // fill tree with data
        return 0;

    run_acinator (tree, file_output);                          // run the acinator program

    build_graphviz (tree);                                     // build tree in graphviz

    tree_dtor (tree);                                          // destroy the tree

    return 0;
}


