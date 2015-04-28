#include <stdlib.h>
#include <stdio.h>
#include "table.h"

/* private methods */

void *table_delete_at(list **l, bool free_elem){
    void *v = (*l)->value;
    list *ll = *l;
    *l = (*l)->next;
    free(ll);
    if(free_elem)
        free(v);
    return v;
}

list *table_list_new(void *x, list *next){
    list *l = calloc(sizeof(list), 1);
    l->value = x;
    l->next  = next;
    return l;
}

void *table_list_insert(list *l, table_comp comp, void *x){
    while(l->next && comp(x, l->next) > 0){
        l = l->next;
    }
    l->next = table_list_new(x, l->next);
    return l->next;
}

void *table_list_delete(list *l, table_comp comp, void *x, bool free_elem){
    if(!l->next)
        return 0;
    else if(comp(l->next->value, x) == 0)
        return table_delete_at(&l->next, free_elem);
    else
        return table_list_delete(l->next, comp, x, free_elem);
}


/* public methods */

table *table_new(table_comp comp, table_hash hash, unsigned size) {
    table *t = calloc(sizeof(table), 1);
    t->row = calloc(sizeof(list *), size);
    t->hash = hash;
    t->comp = comp;
    t->size = size;
    return t;
}

void table_insert(table *t, void *x){
    unsigned i = t->hash(x, t->size);
    if(t->row[i] == 0)
        t->row[i] = table_list_new(x, 0);
    else
        table_list_insert(t->row[i], t->comp, x);
}

void *table_fetch(table *t, void *x){
    unsigned h = t->hash(x, t->size);
    list *l = t->row[h];
    while(l && t->comp(l->value, x) != 0){
        l = l->next;
    }
    return (l && t->comp(l->value, x) == 0) ? l->value : 0;
}

void *table_delete(table *t, void *x, bool free_elem){
    unsigned i = t->hash(x, t->size);
    if(t->row[i] && t->comp(t->row[i]->value, x) == 0){
        return table_delete_at(&t->row[i], free_elem);
    }
    else{
        return table_list_delete(t->row[i], t->comp, x, free_elem);
    }
}

void table_free(table *t, bool free_elems){
    int i;
    for(i = 0; i < t->size; i++){
        list *l = t->row[i];
        while(l != 0){
            list *n = l->next;
            if(free_elems)
                free(l->value);
            free(l);
            l = n;
        }
    }
    free(t->row);
    free(t);
}
