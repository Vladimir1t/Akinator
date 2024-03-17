#include "..\include\tree.h"

FILE* file_error = fopen ("file_error.txt", "w");

int run_acinator (struct node_tree* node)
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
            return INPUT_ERROR;

        if (choice == 'y')
        {
            if (node->right == NULL)
            {
                if (choice == 'y')
                {
                    printf (" Oh, yes! \n");
                    return SUCCESS;
                }

                else if (choice == 'n')
                {
                    node_insert (node, root);
                    break;
                }
            }
            else
                node = node->right;
        }
        else if (choice == 'n')
        {
            if (node->left == NULL)
            {
                if (choice == 'y')
                {
                    printf (" Oh, yes! \n");
                    return SUCCESS;
                }

                else if (choice == 'n')
                {
                    node_insert (node, root);
                    break;
                }
            }
            else
                node = node->left;
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
    struct node_tree* node_new_left  = {0};
    struct node_tree* node_new_right = {0};
    CALLOC (node_new_left,  struct node_tree, 1)
    CALLOC (node_new_right, struct node_tree, 1)
    CALLOC (node_new_right->data, char, DATA_SIZE)

    printf (" What/Who is it? \n");
    scanf ("%s", node_new_right->data);
    clean_buffer ();
    if (node_search (root, node_new_right->data) == SUCCESS)
    {
        printf (" Already exist \n");
        return ERROR;
    }
    //printf ("right << %s >>\n", node_new_right)
    CALLOC (node_new_left->data, char, DATA_SIZE)
    node_new_left->data = node->data;               // put prev leaf in new node
    add_discription (node);

    node->right = node_new_right;
    node->left  = node_new_left;

    return SUCCESS;
}

int add_discription (struct node_tree* node)
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


int node_search (struct node_tree* node, elem_t elem)
{
    if (node == NULL)
    {
        fprintf (file_error, "-- NULL ptr --\n");
        return ERROR;
    }
    if (node->data == elem)
        return SUCCESS;

    if (node->left != NULL)
        node_search (node->left, elem);

    if (node->right != NULL)
        node_search (node->right, elem);

    return ERROR;
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
    fprintf (file_output, "{" SPEC, node->data);
    if (node->left != NULL)
        tree_output (file_output, node->left);

    if (node->right != NULL)
        tree_output (file_output, node->right);

    fprintf (file_output, "}");

    return 0;
}

int get_database (struct node_tree* root, char* file_input)   // get data of tree in the following file
{

    struct node_tree* prev_node = NULL;
    struct node_tree* node      = NULL;
    struct stack      stk       = {0};

    FOPEN (file_p, file_input, "r")
    size_t file_size = file_size_measure (file_p);            // measures the size of a text
    //printf ("size of file: %d\n", file_size);

    char* text_data = NULL;
    CALLOC (text_data, char, file_size + 1)

    size_t factual_size = fread (text_data, sizeof (char), file_size, file_p);
    if (factual_size != file_size)
    {
        fprintf (file_error, "<< Error. Wrong size of data_file >>\n");
        return 0;
    }
    fclose (file_p);

    for (int i = 0, n = 0, position = 0; i < file_size; i++)
    {
        if (text_data[i] == '{' && i == 0)                  // add a root of the tree
        {
            i++;
            while (text_data[i] != '{' && text_data[i] != '}')
            {
                root->data[n] = text_data[i];
                i++;
                n++;
            }
            root->data[n] = '\0';
            //printf ("<< %s >>\n", root->data);

            stack_push (&stk, &root);
            stack_push (&stk, &root);
            position += 2;
        }
        if (text_data[i] == '{')
        {
            i++;
            struct node_tree* node = NULL;
            CALLOC (node, struct node_tree, 1)
            CALLOC (node->data, char, DATA_SIZE)
            n = 0;
            while (text_data[i] != '{' && text_data[i] != '}')
            {
                node->data[n] = text_data[i];
                //printf ("%c ", node->data[n]);
                i++;
                n++;
            }
            node->data[n] = '\0';
            //printf ("<< %s >>\n", node->data);
            stack_pop (&stk, &prev_node);

            if (position % 2 == 0)         // add node as a left leaf
                prev_node->left = node;
            if (position % 2 == 1)         // add node as a right leaf
                prev_node->right = node;

            if (text_data[i] == '{')
            {
                stack_push (&stk, &node);
                stack_push (&stk, &node);
                position += 2;
            }
            i--;
        }
        else if (text_data[i] == '}')
            position--;
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


 /*
int compare (struct node_tree* root, char* first_elem, char* second_elem)
{

}

/*
void build_graphviz (struct node_tree* root, Agraph_t* graph)
{
    if (root == NULL)
    {
        return;
    }

    // Создать узел для текущего узла дерева
    Agnode_t* current_node = agnode (graph, NULL, 1);
    agset (current_node, "label", agstrdup(graph, "%d", root->data));

    // Рекурсивно построить граф для левого и правого поддеревьев
    if (root->left != NULL)
    {
        Agnode_t* left_node = agnode (graph, NULL, 1);
        agset (left_node, "label", agstrdup (graph, "%d", root->left->data));
        agedge (graph, current_node, left_node, NULL, 1);
        build_graphviz (root->left, graph);
    }

    if (root->right != NULL)
    {
        Agnode_t* right_node = agnode (graph, NULL, 1);
        agset (right_node, "label", agstrdup(graph, "%d", root->right->data));
        agedge (graph, current_node, right_node, NULL, 1);
        build_graphviz (root->right, graph);
    }
}

// Функция для сохранения графа в файл в формате DOT
void save_graphviz (Agraph_t *graph, const char* filename)
{
    FILE* file = fopen (filename, "w");
    agwrite (graph, file);
    fclose (file);
}
     */
