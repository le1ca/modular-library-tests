#ifndef table_h
#define table_h

#include <stdbool.h>

/* comparator function */
typedef int      (*table_comp)(void *a, void *b);

/* hashing function */
typedef unsigned (*table_hash)(void *x, unsigned mod);

/* linked list */
typedef struct list_s {
    void          *value;
    struct list_s *next;
} list;

/* hash table */
typedef struct table_s {
    table_hash  hash;
    table_comp  comp;
    unsigned    size;
    list      **row;
} table;

/* functions */
table *table_new(table_comp comp, table_hash hash, unsigned size);
void   table_insert(table *t, void *x);
void  *table_fetch (table *t, void *x);
void  *table_delete(table *t, void *x, bool free_elem);
void   table_free  (table *t, bool free_elems);

#endif
