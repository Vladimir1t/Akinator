#include "..\include\stack_path.h"

FILE* ERROR_FILE_PATH = fopen ("Log\\file_error_stack_path.txt", "w");

void stack_path_ctor (struct stack_path* stk, const size_t capacity)
{
    if (capacity <= 0)
        fprintf (ERROR_FILE_PATH, "<< Error. Capacity <= 0 >>\n");
    stk->size = 0;
    stk->capacity = capacity;
    stk->data = (elem_t_path*) calloc (stk->capacity, sizeof(elem_t_path));

    if (stk->data == NULL)
        fprintf (ERROR_FILE_PATH, "<< ERROR. Calloc >>\n");

    for (int i = 0; i < capacity; i++)
        stk->data[i] = POISON_PATH;

    verifier_path (stk);
}

void stack_path_push (struct stack_path* stk, const elem_t_path value)
{
    verifier_path (stk);

    if (stk->size == stk->capacity)
        stack_path_realloc_increase (stk);

    stk->data[stk->size] = value;

    stk->size++;

    verifier_path (stk);
}

void stack_path_pop (struct stack_path* stk, elem_t_path* element)
{
    verifier_path (stk);

    if (element == NULL)
        fprintf (ERROR_FILE_PATH, "<< NULL PTR >>\n");

    if (stk->size == 0)
        fprintf (ERROR_FILE_PATH, "<< there are no numbers to be popped >>\n");

    if (stk->size * 4 < stk->capacity)
        stack_path_realloc_decrease (stk);

    *element = stk->data[stk->size - 1];
    stk->data[stk->size - 1] = POISON_PATH;

    stk->size--;

    verifier_path (stk);
}

void stack_path_dtor (struct stack_path* stk)
{
    verifier_path (stk);

    for (size_t i = 0; i < stk->size; i++)
        stk->data[i] = POISON_PATH;

    stk->capacity = 0;
    stk->size = 0;

    free (stk->data);

    stk->data = NULL;
}

int stack_path_realloc_increase (struct stack_path* stk)
{
     verifier_path (stk);

     elem_t_path* pointer = stk->data;
     stk->data = (elem_t_path*) realloc (stk->data, (stk->capacity * 2) * sizeof (elem_t_path));

     if (stk->data == NULL)
     {
        stk->data = pointer;
        fprintf (ERROR_FILE_PATH, "<< Realloc increase error >>\n");
        return REALLOC_ERR;
     }
     for (int i = stk->capacity; i < stk->capacity * 2; i++)
        stk->data[i] = POISON_PATH;

     stk->capacity *= 2;

     verifier_path (stk);

     return REALLOC_OK;
}

int stack_path_realloc_decrease (struct stack_path* stk)
{
     verifier_path (stk);

     elem_t_path* pointer = stk->data;
     stk->data = (elem_t_path*) realloc (stk->data, (stk->capacity / 2) * sizeof (elem_t_path));
     if (stk->data == NULL)
     {
        stk->data = pointer;
        fprintf (ERROR_FILE_PATH, "<< Realloc decrease error >>\n");
        return REALLOC_ERR;
     }
     stk->capacity /= 2;

     verifier_path (stk);

     return REALLOC_OK;
}

void dump_path (struct stack_path* stk, FILE* logFile)
{
    verifier_path (stk);
    if (logFile == NULL)
        fprintf (ERROR_FILE_PATH, "<< NUL ptr >>\n");

    fprintf (logFile, "--------------------\n");
    fprintf (logFile, "---- stack_path dump ----\n");
    fprintf (logFile, "--------------------\n");

    fprintf (logFile, "capacity: %d\n", stk->capacity);
    fprintf (logFile, "size: %d\n", stk->size);

    for (int i = 0; i < stk->size; i++)
        fprintf (logFile, "[%d] " SPEC_STK_PATH "\n", i, stk->data[i]);
    fprintf (logFile, "--------------------\n");

    for (int i = stk->size; i < stk->capacity; i++)
        fprintf (logFile, "[%d] " SPEC_STK_PATH "\n", i, stk->data[i]);
    fprintf (logFile, "--------------------\n");

    verifier_path (stk);
}

void verifier_path (struct stack_path* stk)
{
    if (stk == NULL)
        fprintf (ERROR_FILE_PATH, "Error: stack_path = NULL\n");

    if (stk->data == NULL)
        fprintf (ERROR_FILE_PATH, "Error: stk.data = NULL\n");

    if (stk->capacity < stk->size)
        fprintf (ERROR_FILE_PATH, "Error: capacity < size\n");

    if (stk->capacity < 0)
        fprintf (ERROR_FILE_PATH, "ERROR: capacity < 0\n");

    if (stk->size < 0)
        fprintf (ERROR_FILE_PATH, "ERROR: size < 0\n");

    for (int i = 0; i < stk->size; i++)
    {
        if (stk->data[i] == POISON_PATH)
            fprintf (ERROR_FILE_PATH, "element [%d] = POISON_PATH value\n", i);
    }
    for (int i = stk->size; i < stk->capacity; i++)
    {
        if (stk->data[i] != POISON_PATH)
            fprintf (ERROR_FILE_PATH, "element [%d] != POISON_PATH value\n", i);
    }
}

size_t stack_look (stack_path* stk, elem_t_path** array)
{
    *array = (elem_t_path*) calloc (stk->size, sizeof (elem_t_path));
    memcpy (*array, stk->data, sizeof (elem_t_path) * stk->size);
    //printf (" < node path > \n");
    //printf ("\n");
    return stk->size;
}
