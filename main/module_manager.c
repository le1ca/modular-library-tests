#include <dlfcn.h>
#include <stdio.h>
#include "module_manager.h"
#include "module_table.h"

void module_load(char filename[]){
    void *hdl = dlopen(filename, RTLD_LAZY);
    char *name = dlsym(hdl, "module_name");
    unsigned *func_ct = dlsym(hdl, "module_func_ct");
    char **func_names = dlsym(hdl, "module_func_names");
    module *m = mt_new_module(name, hdl);
    unsigned i;
    for(i = 0; i < *func_ct; i++){
        char *fn_name = (func_names)[i];
        void *fn_ptr = dlsym(hdl, (func_names)[i]);
        mt_insert(m, fn_name, fn_ptr);
    }
}

void module_call(char *fn_name, void *arg){
    module_entry *e = mt_get(fn_name);
    e->fun(arg);
}
