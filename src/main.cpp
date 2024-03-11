#include "..\include\tree.h"

int main()
{
    setlocale (LC_ALL, "Rus");

    struct node_tree* tree = (struct node_tree*) calloc (1, sizeof (struct node_tree));
    //tree->data = (char*) calloc (DATA_SIZE, sizeof(char));
    tree->data = "�������";

    struct node_tree* node1 = (struct node_tree*) calloc (1, sizeof (struct node_tree));
    struct node_tree* node2 = (struct node_tree*) calloc (1, sizeof (struct node_tree));
    node1->data = "���";
    node2->data = "����������";
    tree->left = node2;
    tree->right = node1;

    char mode = '\0';
    while (mode != 's')
    {
        node_insert (tree);
        printf ("write 's' to stop the program\n");
        scanf ("%c", &mode);
    }

    tree_print (tree);

     // ������� ���� Graphviz
    Agraph_t *graph = agopen ("tree", Agdirected, NULL);

    // ��������� ���� �� ������
    build_graphviz (root, graph);

    // ��������� ���� � ����
    save_graphviz (graph, "tree.dot");

    // ���������� ������
    agclose (graph);

    tree_dtor (tree);

    return 0;
}
