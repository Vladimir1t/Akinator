#include "..\include\acinator.h"

static FILE* file_error = fopen ("Log\\file_error_acinator.txt", "w");

int run_acinator (struct node_tree* node, FILE* file_output)
{
    char element[DATA_SIZE] = {0};
    char mode = '\0';

    printf ("-- AKINATOR --\n");
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
                play_acinator (node);
                break;

            case 'f':
                printf ("write smb to find in tree\n");
                fgets (element, DATA_SIZE, stdin);
                element[strlen (element) - 1] = '\0';
                give_information (element, node);
                break;
        }
    }

    printf ("do you want to add new data to a database?\n"
            "( y, n )\n");
    scanf ("%c", &mode);
    if (mode == 'y')
        tree_output (file_output, node);    // add data in file_output

    return SUCCESS;
}

int play_acinator (struct node_tree* node)
{
    char choice = '\0';
    struct node_tree* root = node;

    while (1)
    {
        printf (" %s ?\n", node->data);
        printf ("( y, n )\n");
        scanf ("%c", &choice);
        clean_buffer ();
        if (choice != 'y' && choice != 'n')
            printf (" try again \n");

        if (choice == 'y')
        {
            if (node->right == NULL)
            {
                printf (" Oh, yes! \n");
                return SUCCESS;
            }
            else
            {
                node = node->right;
            }
        }
        else if (choice == 'n')
        {
            if (node->left == NULL)
            {
                node_insert (node, root);
                break;
            }
            else
            {
                node = node->left;
            }
        }
    }
    return SUCCESS;
}

int compare (struct node_tree* root, char* first_elem, char* second_elem)
{

}

