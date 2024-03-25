#include "..\include\acinator.h"

static FILE* file_error = fopen ("Log\\file_error_tree.txt", "w");

void tree_dtor (struct node_tree* node)
{
    if (node->left != NULL)
        tree_dtor (node->left);

    if (node->right != NULL)
        tree_dtor (node->right);

    node->data = POISON;
    free (node);
}

int node_insert (struct node_tree* node, struct node_tree* root)
{
    struct node_tree* node_new_left  = {0};
    struct node_tree* node_new_right = {0};

    CALLOC (node_new_left,  struct node_tree, 1)
    CALLOC (node_new_right, struct node_tree, 1)
    CALLOC (node_new_right->data, char, DATA_SIZE)

    printf (" What/Who is it? \n");
    fgets (node_new_right->data, DATA_SIZE, stdin);
    node_new_right->data[strlen (node_new_right->data) - 1] = '\0';
    //clean_buffer ();

    if (give_information (node_new_right->data, root) != ERROR)
        return ERROR;

    CALLOC (node_new_left->data, char, DATA_SIZE)
    node_new_left->data = node->data;               // put prev leaf in new node
    add_description (node);

    node->right = node_new_right;
    node->left  = node_new_left;

    return SUCCESS;
}

int add_description (struct node_tree* node)
{
    char* information = NULL;
    CALLOC (information, char, DATA_SIZE)

    printf (" What is unique about it/him? \n");
    //if (scanf ("%s", information) != 1)
    //    return ERROR;
    if (fgets (information, DATA_SIZE, stdin) == NULL)
        return ERROR;
    clean_buffer ();
    node->data = information;

    return SUCCESS;
}

int give_information (elem_t element, struct node_tree* node)
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

int node_search (struct node_tree* node, elem_t elem, stack_path* stk_path)
{
    elem_t_path wrong_node = POISON_PATH;

    if (node == NULL)
    {
        fprintf (file_error, "-- NULL ptr --\n");
        return ERROR;
    }
    if (!strcmp (node->data, elem))
    {
        return SUCCESS;
    }

    if (node->left != NULL)
    {
        stack_path_push (stk_path, NO);
        if (node_search (node->left, elem, stk_path) == SUCCESS)
            return SUCCESS;
        stack_path_pop (stk_path, &wrong_node);
    }

    if (node->right != NULL)
    {
        stack_path_push (stk_path, YES);
        if (node_search (node->right, elem, stk_path) == SUCCESS)
            return SUCCESS;
        stack_path_pop (stk_path, &wrong_node);
    }
}

void clean_buffer ()
{
    int symbol = 0;
    do
    {
        symbol = getchar ();
    }
    while (symbol != '\n' && symbol != EOF);
}





