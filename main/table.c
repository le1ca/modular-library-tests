#include <stdlib.h>
#include <string.h>
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
    list *l = malloc(sizeof(list));
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
    do{
        if(l->next && comp(l->next->value, x) == 0){
            return table_delete_at(&l->next, free_elem);
        }
        l = l->next;
    } while(l && comp(l->value, x) < 0);
    return 0;
}


/* public methods */

table *table_new(table_comp comp, table_hash hash, unsigned size) {
    table *t = malloc(sizeof(table) + size*sizeof(list *));
    t->hash = hash;
    t->comp = comp;
    t->size = size;
    memset(t->row, 0, size*sizeof(list*));
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
    list *l = t->row[t->hash(x, t->size)];
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
    free(t);
}
