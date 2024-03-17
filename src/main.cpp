#include "..\include\tree.h"

int main(int argc, char* argv[])
{
    setlocale (LC_ALL, "Rus");
    FOPEN (file_output, "file_output.txt", "a")

    struct node_tree* tree = NULL;
    CALLOC (tree, struct node_tree, 1)
    CALLOC (tree->data, char, DATA_SIZE)

    /*(struct node_tree*) calloc (1, sizeof (struct node_tree));
    tree->data = (char*) calloc (DATA_SIZE, sizeof(char));
    tree->data = "человек";

    struct node_tree* node1 = (struct node_tree*) calloc (1, sizeof (struct node_tree));
    struct node_tree* node2 = (struct node_tree*) calloc (1, sizeof (struct node_tree));
    node1->data = "Дед";
    node2->data = "Полторашка";
    tree->left = node2;
    tree->right = node1;      */

    if (argc == 2)
        if (get_database (tree, argv[1]) != SUCCESS)
            return 0;

    printf ("-- AKINATOR --\n");

    char mode = '\0';
    while (mode != 's')
    {
        printf ("choose what you want to do:\n"
                "'p' to play, 'f' to find an element or 's' to stop\n");
        scanf ("%c", &mode);
        clean_buffer ();

        switch (mode)
        {
            case 's':
                break;
            case 'p':
                run_acinator (tree);
                break;

            case 'f':
                printf ("find\n");
                break;
        }
    }
    printf ("do you want to add new data to a database?\n"
            "( y, n )\n");

    scanf ("%c", &mode);
    if (mode == 'y')
        tree_output (file_output, tree);


    /* Создать граф Graphviz
    Agraph_t *graph = agopen ("tree", Agdirected, NULL);

    // Построить граф из дерева
    build_graphviz (root, graph);

    // Сохранить граф в файл
    save_graphviz (graph, "tree.dot");

    // Освободить память
    agclose (graph);      */

    tree_dtor (tree);

    return 0;
}
