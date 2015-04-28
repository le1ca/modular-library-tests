#include <stdio.h>

char      module_name[]       = "foo-module";
unsigned  module_func_ct      = 2;
char     *module_func_names[] = { "foo_set", "foo_hello" };

__attribute__((constructor))
void foo_init(){
    
}

__attribute__((destructor))
void foo_destroy(){
    
}

void foo_set(void *arg){
    printf("foo_set!\n");
}

void foo_hello(void *arg){
    printf("foo_hello!\n");
}
