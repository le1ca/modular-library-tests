#include "foo-mod.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

foo_obj *f;

__attribute__((constructor))
void foo_init(){
    f = malloc(sizeof(foo_obj));
    strncpy(f->param, "Hello, world!", FOO_PARAM_LEN);
}

__attribute__((destructor))
void foo_destroy(){
    free(f);
}

void foo_set(const char s[]){
    strncpy(f->param, s, FOO_PARAM_LEN);
}

void foo_hello(){
    printf("%8p: %s\n", (void *) f, f->param);
}
