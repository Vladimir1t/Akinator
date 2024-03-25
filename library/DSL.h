#ifndef DSL_H_INCLUDED
#define DSL_H_INCLUDED

/* Library of defines */

#define checkPtr(ptr)     \
    if (ptr == NULL)      \
        return NULL_PTR;  \


#define REALLOC(elem, type, size)                            \
    do                                                       \
    {                                                        \
        void* clTmp = realloc (elem, size * sizeof (type));  \
        if (clTmp == NULL)                                   \
            return REALLOC_ERROR;                            \
        elem = (type*) clTmp;                                \
    }                                                        \
    while (0);


#define CALLOC(elem, type, size)                     \
    do                                               \
    {                                                \
        void* clTmp = calloc (size, sizeof (type));  \
        if (clTmp == NULL)                           \
            return CALLOC_ERROR;                     \
        elem = (type*) clTmp;                        \
    }                                                \
    while (0);


#define FOPEN(ptr, name, mode)           \
        FILE* ptr = fopen (name, mode);  \
        if (ptr == NULL)                 \
            return OPEN_ERROR;           \



#endif // DSL_H_INCLUDED
