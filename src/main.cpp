#include "..\include\tree.h"

int main(int argc, char* argv[])
{
    setlocale (LC_ALL, "Rus");
    FOPEN (file_output, "file_output.txt", "a")

    struct node_tree* tree = NULL;
    CALLOC (tree, struct node_tree, 1)
    CALLOC (tree->data, char, DATA_SIZE)


    if (argc == 2 && get_database (tree, argv[1]) != SUCCESS)
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


    // ��������� ���� �� ������
    build_graphviz (tree);



    tree_dtor (tree);

    return 0;
}


