#include <stdio.h>
#include <dlfcn.h>
#include "foo-mod.h"

int main(int argc, char **argv){
    void *foo_mod_hdl;
    void (*foo_set_f)(const char s[]);
    void (*foo_hello_f)();
    char *err;

    // load foo-mod library
    if(!(foo_mod_hdl = dlopen("foo-mod.so", RTLD_LAZY))){
        fprintf(stderr, "Error loading module: %s\n", dlerror());
        return 0;
    }
    
    // get reference to foo_set function
    foo_set_f = dlsym(foo_mod_hdl, "foo_set");
    if((err = dlerror()) != NULL){
        fprintf(stderr, "Error referencing function: %s\n", err);
        return 0;
    }
    
    // get reference to foo_hello function
    foo_hello_f = dlsym(foo_mod_hdl, "foo_hello");
    if((err = dlerror()) != NULL){
        fprintf(stderr, "Error referencing function: %s\n", err);
        return 0;
    }

    // do the thing
    (*foo_hello_f)();
    (*foo_set_f)("foo bar");
    (*foo_hello_f)();


    // release the library
    dlclose(foo_mod_hdl);

    return 0;
}
