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
                printf ("Write smb to find in tree\n");
                fgets (element, DATA_SIZE, stdin);
                element[strlen (element) - 1] = '\0';
                give_node_information (element, node);
                break;

            case 'c':
                compare_two_nodes (node);
                break;
        }
    }

    printf ("Do you want to add new data to a database?\n"
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

int give_node_information (elem_t element, struct node_tree* node)
{
    elem_t_path*      path           = NULL;
    size_t            len_path       = 0;
    struct stack_path stk_path       = {0};

    stack_path_ctor (&stk_path, 2);

    if (node_search (node, element, &stk_path) == SUCCESS)
    {
        printf ("< exist in tree >\n");
        len_path = stack_look (&stk_path, &path);
    }
    else
    {
        printf ("< don't exist >\n");
        return ERROR;
    }

    stack_path_dtor (&stk_path);

    for (int i = 0; i < len_path; i++)
    {
        if (path[i] == NO)
        {
            printf ("not %s", node->data);
            node = node->left;
        }
        else /* path[i] == YES */
        {
            printf ("%s", node->data);
            node = node->right;
        }
        if (i < len_path - 1)
            printf (", ");
    }
    printf ("\n\n");

    return SUCCESS;
}

int compare_two_nodes (struct node_tree* node)
{
    elem_t_path*      path_1     = NULL;
    size_t            len_path_1 = 0;
    struct stack_path stk_path_1 = {0};

    elem_t_path*      path_2     = NULL;
    size_t            len_path_2 = 0;
    struct stack_path stk_path_2 = {0};
    char element_1[DATA_SIZE]    = {0};
    char element_2[DATA_SIZE]    = {0};

    stack_path_ctor (&stk_path_1, 2);
    stack_path_ctor (&stk_path_2, 2);

    printf (" Write two elements, which you want to compare\n "
            " first\n ");
    fgets (element_1, DATA_SIZE, stdin);
    element_1[strlen (element_1) - 1] = '\0';
    clean_buffer ();

    printf (" second \n ");
    fgets (element_2, DATA_SIZE, stdin);
    element_2[strlen (element_2) - 1] = '\0';

    printf ("first: %s\n", element_1);
    printf ("second: %s\n", element_2);


    if (node_search (node, element_1, &stk_path_1) == SUCCESS)
    {
        printf ("ok\n");
        len_path_1 = stack_look (&stk_path_1, &path_1);
    }
    else
    {
        printf ("< don't exist 1 >\n");
        return ERROR;
    }

    if (node_search (node, element_2, &stk_path_2) == SUCCESS)
    {
         printf ("ok\n");
        len_path_2 = stack_look (&stk_path_2, &path_2);
    }
    else
    {
        printf ("< don't exist 2 >\n");
        return ERROR;
    }

    stack_path_dtor (&stk_path_1);
    size_t max_len = (len_path_1 > len_path_2) ? len_path_1 : len_path_2;

    for (int i = 0; i < len_path_1; i++)
    {
        if (path_1[i] == NO)
        {
            printf ("not %s", node->data);
            node = node->left;
        }
        else /* path[i] == YES */
        {
            printf ("%s", node->data);
            node = node->right;
        }
        if (i < len_path_1 - 1)
            printf (", ");
    }
    printf ("\n\n");

  /*  for (int i = 0; i < max_len; i++)
    {
        if ()
    }      */
}

