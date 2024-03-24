#include "..\include\tree.h"

static FILE* file_error = fopen ("Log\\file_error.txt", "w");


int run_acinator (struct node_tree* node, FILE* file_output)
{
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
                play_acinator (node);
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
            printf (" try again\n");

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
    int               search_result  = ERROR;
    struct stack      stk_desription = {0};
    elem_t_stk*       array_desrciption = NULL;
    struct node_tree* node_new_left  = {0};
    struct node_tree* node_new_right = {0};

    CALLOC (node_new_left,  struct node_tree, 1)
    CALLOC (node_new_right, struct node_tree, 1)
    CALLOC (node_new_right->data, char, DATA_SIZE)

    printf (" What/Who is it? \n");
    scanf ("%s", node_new_right->data);
    clean_buffer ();
    node_search (root, node_new_right->data, &search_result, &stk_desription);
    printf ("[%d]\n", search_result);
    if (search_result == SUCCESS)
    {
        printf (" Already exist \n");
        stack_look (&stk_desription, array_desrciption);
        return ERROR;
    }
    //printf ("right << %s >>\n", node_new_right)
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
    if (scanf ("%s", information) != 1)
        return ERROR;
    clean_buffer ();
    node->data = information;

    return SUCCESS;
}

int node_search (struct node_tree* node, elem_t elem, int* search_result, struct stack* stk_description)
{
    printf ("funct\n");
    elem_t_stk wrong_node = POISON_STK;

    stack_push (stk_description, &node);
    if (node == NULL)
    {
        fprintf (file_error, "-- NULL ptr --\n");
        *search_result = ERROR;
    }
    if (!strcmp (node->data, elem))
    {
        printf ("find\n");
        *search_result = SUCCESS;
        return SUCCESS;

    }

    if (node->left != NULL)
    {
        node_search (node->left, elem, search_result, stk_description);

    }

    stack_pop (stk_description, &wrong_node);

    if (node->right != NULL)
    {
        node_search (node->right, elem, search_result, stk_description);
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


int tree_output (FILE* file_output, struct node_tree* node)
{
    fprintf (file_output, "{ \"" SPEC "\" ", node->data);
    if (node->left != NULL)
        tree_output (file_output, node->left);

    if (node->right != NULL)
        tree_output (file_output, node->right);

    fprintf (file_output, "}");

    return 0;
}

int get_database (struct node_tree* root, char* file_input)   // get data of tree in the following file
{
    FOPEN (file_p, file_input, "rb")
    size_t file_size = file_size_measure (file_p);            // measures the size of a text
    //printf ("size of file: %d\n", file_size);

    char* text_data = NULL;
    CALLOC (text_data, char, file_size + 1)

    size_t factual_size = fread (text_data, sizeof (char), file_size, file_p);
    if (factual_size != file_size)
    {
        fprintf (file_error, "<< Error. Wrong size of data_file >>\n");
        return ERROR;
    }
    fclose (file_p);

    construct_data_nodes (root, text_data, file_size);

    return SUCCESS;
}

int construct_data_nodes (struct node_tree* root, char* text_data, size_t file_size)
{
    struct node_tree* prev_node = NULL;
    struct node_tree* node      = NULL;
    struct stack      stk       = {0};

    stack_ctor (&stk, 2);
    for (int i = 0, n = 0, position = ROOT; i < file_size; i++)
    {
        if (text_data[i] == '{' && position == ROOT)  // add a root of the tree
        {
            while (text_data[i] != '"')               // search for a beginning of a new word
                 i++;
            i++;

            while (text_data[i] != '"')               // fill buffer with a new word
            {
                root->data[n] = text_data[i];
                i++;
                n++;
            }
            root->data[n] = '\0';
            printf ("<< %s >>\n", root->data);

            stack_push (&stk, &root);
            stack_push (&stk, &root);
            position = LEFT;
        }
        if (text_data[i] == '{')                      // add node in tree
        {
            struct node_tree* node = NULL;
            CALLOC (node, struct node_tree, 1)
            CALLOC (node->data, char, DATA_SIZE)
            n = 0;
            while (text_data[i] != '"')               // search for a beginning of a new word
                i++;
            i++;

            while (text_data[i] != '"')               // fill buffer with a new word
            {
                node->data[n] = text_data[i];
                i++;
                n++;
            }
            node->data[n] = '\0';
            printf ("<< %s >>\n", node->data);
            stack_pop (&stk, &prev_node);

            if (position == LEFT)                     // add node as a left leaf
            {
                prev_node->left = node;
            }
            else                                      // add node as a right leaf
            {
                prev_node->right = node;
            }

            while (text_data[i] != '{' && text_data[i] != '}')
            {
                i++;
            }
            if (text_data[i] == '{')                  // next node will be in a left position
            {
                stack_push (&stk, &node);
                stack_push (&stk, &node);
                position = LEFT;
            }
            i--;
        }
        else if (text_data[i] == '}')                 // if a next node will be, it will stay in a right position
        {
            position = RIGHT;
        }
    }
    stack_dtor (&stk);

    return SUCCESS;
}

size_t file_size_measure (FILE* const file_p)
{
    assert (file_p != NULL);

    int start_position = ftell (file_p);

    fseek (file_p, 0, SEEK_END);
    size_t len = (size_t) ftell (file_p);

    fseek (file_p, start_position, SEEK_SET);

    return len;
}


int compare (struct node_tree* root, char* first_elem, char* second_elem)
{

}

int build_graphviz (struct node_tree* root)
{
    size_t node_num = 0;
    if (root == NULL)
        return ERROR;

    FOPEN (file_graph, "graphviz\\graph.dot", "w")

    fprintf (file_graph, "digraph AKINATOR{\n"
                         "label = < AKINATOR >;\n"
                         "bgcolor = \"#BAF0EC\";\n"
                         "node [shape = record ];\n"
                         "edge [style = filled ];\n");

      /*   create a tree in graphviz   */
    add_node_in_graph_1 (root, file_graph, &node_num);
    add_node_in_graph_2 (root, file_graph);
    fprintf (file_graph, "}");

    fclose (file_graph);
}

void add_node_in_graph_1 (struct node_tree* node, FILE* file_graph, size_t* node_num)
{

    char* buffer = (char*) calloc (strlen (node->data) + 3, sizeof (char));
    buffer[0] = '"';
    strcat (buffer, node->data);
    buffer[strlen (node->data) + 1] = '"';

    if (node->right == NULL && node->left == NULL)
    {
        fprintf (file_graph, " %d [shape = Mrecord, style = filled, fillcolor = YellowGreen, label = %s ];\n", *node_num, buffer);
        node->num_in_tree = *node_num;
        //printf ("[%d]\n", node->num_in_tree);
    }
    else
    {
        fprintf (file_graph, " %d [shape = Mrecord, style = filled, fillcolor = Peru, label = %s ];\n", *node_num, buffer);
        node->num_in_tree = *node_num;
        //printf ("[%d]\n", node->num_in_tree);
    }
    if (node->left != NULL)
    {
        *node_num += 1;
        add_node_in_graph_1 (node->left, file_graph, node_num);
    }

    if (node->right != NULL)
    {
        *node_num += 1;
        add_node_in_graph_1 (node->right, file_graph, node_num);
    }
}

void add_node_in_graph_2 (struct node_tree* node, FILE* file_graph)
{
    if (node->left != NULL)
    {
        fprintf (file_graph, "%d -> %d[label = n] [ color = Peru ];\n", node->num_in_tree, (node->left)->num_in_tree);
        add_node_in_graph_2 (node->left, file_graph);
    }

    if (node->right != NULL)
    {
        fprintf (file_graph, "%d -> %d[label = y] [ color = Peru ];\n", node->num_in_tree, (node->right)->num_in_tree);
        add_node_in_graph_2 (node->right, file_graph);
    }
}




