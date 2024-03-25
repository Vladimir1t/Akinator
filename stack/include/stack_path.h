#ifndef stack_path_PATH_H_INCLUDED
#define stack_path_PATH_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "..\..\include\acinator.h"

#define SPEC_STK_PATH "%d"

typedef int elem_t_path;
const elem_t_path POISON_PATH = 0xDEAD;

struct stack_path
{
    size_t       capacity;
    size_t       size;
    elem_t_path* data;
};

enum Element
{
    NO  = 0,
    YES = 1,
};

void stack_path_ctor (stack_path* stk, const size_t capacity);

void stack_path_push (stack_path* stk, const elem_t_path value);

void stack_path_pop  (stack_path* stk, elem_t_path* element);

void stack_path_dtor (stack_path* stk);

int stack_path_realloc_increase (stack_path* stk);

int stack_path_realloc_decrease (stack_path* stk);

void verifier_path (stack_path* stk);

void dump_path (stack_path* stk, FILE* file);

size_t stack_look (stack_path* stk, elem_t_path** array);

#endif // stack_path_PATH_H_INCLUDED
