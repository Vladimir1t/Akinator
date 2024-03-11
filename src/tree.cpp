#include "..\include\tree.h"

int node_insert (struct node_tree* node)
{
    struct node_tree* node_new_left  = {0};
    struct node_tree* node_new_right = {0};
    char* information = (char*) calloc (DATA_SIZE, sizeof(char));
    char              choice         = '\0';

    while (1)
    {
        printf (" %s ?\n", node->data);
        printf ("( y, n )\n");
        scanf ("%c", &choice);
        clean_buffer ();

        if (choice != 'y' && choice != 'n')
            return INPUT_ERROR;

        //printf ("..%c..\n", choice);

        if (choice == 'y')
        {
            if (node->right == NULL)
            {
                //printf (" Is it %s ?\n", node->data);
                //printf ("( y, n )\n");
                //scanf ("%c", &choice);
                //clean_buffer ();

                if (choice != 'y' && choice != 'n')
                    return INPUT_ERROR;

                if (choice == 'y')
                {
                    printf (" Oh, yes! \n");
                    return SUCCESS;
                }

                else if (choice == 'n')
                {
                    node_new_left  = (struct node_tree*) calloc (1, sizeof (struct node_tree));
                    node_new_right = (struct node_tree*) calloc (1, sizeof (struct node_tree));

                    node_new_right->data = (char*) calloc (DATA_SIZE, sizeof(char)); // who
                    printf (" What/Who is it? \n");
                    scanf ("%s", node_new_right->data);
                    //printf ("..%s..\n", node_new_right->data);
                    clean_buffer ();
                    //printf ("right << %s >>\n", node_new_right)

                    node_new_left->data = (char*) calloc (DATA_SIZE, sizeof(char));
                    node_new_left->data = node->data;   // put prev leaf in new node
                    printf (" What is unique about it/him? \n");
                    scanf ("%s", information);
                    node->data = information;
                    //printf ("..%s..\n", node->data);

                    //
                    node->right = node_new_right;
                    node->left  = node_new_left;

                    node_new_right->left = NULL;
                    node_new_right->right = NULL;
                    node_new_left->left = NULL;
                    node_new_left->left = NULL;

                    return SUCCESS;
                }
                //node->left = node_new;
                //break;
            }
            else
                node = node->right;
        }
        else if (choice == 'n')
        {
            if (node->left == NULL)
            {
                //printf (" Is it %s ?\n", node->data);
                //printf ("( y, n )\n");
                //scanf ("%c", &choice);
                //clean_buffer ();

                if (choice != 'y' && choice != 'n')
                    return INPUT_ERROR;

                if (choice == 'y')
                {
                    printf (" Oh, yes! \n");
                    return SUCCESS;
                }

                else if (choice == 'n')
                {
                    node_new_left  = (struct node_tree*) calloc (1, sizeof (struct node_tree));
                    node_new_right = (struct node_tree*) calloc (1, sizeof (struct node_tree));

                    node_new_right->data = (char*) calloc (DATA_SIZE, sizeof(char)); // who
                    printf (" What/Who is it? \n");
                    scanf ("%s", node_new_right->data);
                    clean_buffer ();
                    //printf ("right << %s >>\n", node_new_right)

                    node_new_left->data = (char*) calloc (DATA_SIZE, sizeof(char));
                    node_new_left->data = node->data;   // put prev leaf in new node
                    printf (" What is unique about it/him? \n");
                    scanf ("%s", information);
                    node->data = information;
                    //
                    node->right = node_new_right;
                    node->left  = node_new_left;

                    return SUCCESS;
                }
                //node->left = node_new;
                //break;
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

void tree_print (struct node_tree* node)
{
    printf ("{ " SPEC " ", node->data);
    if (node->left != NULL)
       tree_print (node->left);

    if (node->right != NULL)
        tree_print (node->right);

    printf ("} ");
}

struct node_tree* tree_search (struct node_tree* node, elem_t elem)
{
    while (1)
    {
        if (node->data == elem)
        {
            return node;
        }

        else if (node->data > elem)
        {
            //printf ("elem < node (" SPEC ")\n", node->data);
            if (node->left == NULL)
            {
                return NULL;
            }
            else
                node = node->left;
        }
        else if (node->data < elem)
        {
            //printf ("elem > node (" SPEC ")\n", node->data);
            if (node->right == NULL)
            {
                 return NULL;
            }
            else
                node = node->right;
        }
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

