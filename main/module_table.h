#ifndef module_table_h
#define module_table_h

#include "table.h"

#define MODULE_TABLE_SIZE 128

struct module_entry_s;

typedef struct module_s {
    void *hdl;
    char *name;
    unsigned refs;
    struct module_entry_s *head;
} module;

typedef struct module_entry_s {
    char *fn_name;
    void (*fun)(void *);
    module *module;
    struct module_entry_s *next;
} module_entry;

void          mt_init();
void          mt_destroy();
module       *mt_new_module(char* name, void* hdl);
void          mt_insert(module* m, char* fn_name, void *fun);
void          mt_delete(module* m, char* fn_name);
module_entry *mt_get(char* fn_name);

#endif
