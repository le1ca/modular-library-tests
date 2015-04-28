#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "module_table.h"

/* private variables */

table *module_table;

/* private functions */

int mt_comp(void *a, void *b){
    module_entry *aa = (module_entry *) a;
    module_entry *bb = (module_entry *) b;
    return strcmp(aa->fn_name, bb->fn_name);
}

unsigned mt_hash(void *x, unsigned mod){
    unsigned acc = 0, i;
    module_entry *xx = (module_entry *) x;
    for(i = 0; xx->fn_name[i]; i++){
        acc = (acc + xx->fn_name[i]) % mod;
    }
    return acc;
}

module_entry *mt_new_entry(module* m, char* fn_name, void *fun){
    module_entry *e = malloc(sizeof(module_entry));
    e->fn_name = fn_name;
    e->fun = fun;
    e->module = m;
    e->next = 0;
    return e;
}

void mt_mod_rm_entry(module *m, module_entry *e){
    if(mt_comp(m->head, e) == 0){
        m->head = m->head->next;
    }
    else{
        module_entry *t = m->head;
        while(t->next && mt_comp(t->next, e) != 0)
            t = t->next;
        t->next = t->next->next;
    }
    if(--m->refs == 0){
        dlclose(m->hdl);
        free(m);
    }
}

/* public functions */

void mt_init(){
    module_table = table_new(mt_comp, mt_hash, MODULE_TABLE_SIZE);
}

module *mt_new_module(char* name, void* hdl){
    module *m = malloc(sizeof(module));
    m->name = name;
    m->hdl  = hdl;
    m->refs = 0;
    m->head = 0;
    return m;
}

void mt_insert(module* m, char* fn_name, void *fun){
    module_entry *e = mt_new_entry(m, fn_name, fun);
    if(table_fetch(module_table, e) == 0){
        table_insert(module_table, e);
        e->next = m->head;
        m->head = e;
        m->refs++;
    }
    else{
        free(e);
    }
}

void mt_delete(module* m, char* fn_name){
    module_entry *t = mt_new_entry(0, fn_name, 0);
    module_entry *e = table_delete(module_table, t, false);
    mt_mod_rm_entry(e->module, e);
    free(e);
    free(t);
}

module_entry *mt_get(char* fn_name){
    module_entry *t = mt_new_entry(0, fn_name, 0);
    module_entry *e = table_fetch(module_table, t);
    free(t);
    return e;
}

void mt_destroy(){
    unsigned i;
    for(i = 0; i < module_table->size; i++){
        list *l = module_table->row[i];
        while(l != 0){
            list *n = l->next;
            mt_mod_rm_entry(((module_entry *) l->value)->module, l->value);
            free(l->value);
            free(l);
            l = n;
        }
    }
    free(module_table->row);
    free(module_table);
}
