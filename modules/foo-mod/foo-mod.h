#ifndef foo_mod_h
#define foo_mod_h

#define FOO_PARAM_LEN 16

typedef struct foo_obj_s {
    char param[FOO_PARAM_LEN];
} foo_obj;

void foo_set(const char s[]);
void foo_hello();

#endif
