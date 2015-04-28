#ifndef module_manager_h
#define module_manager_h

void module_load(char filename[]);
void module_call(char *fn_name, void *arg);

#endif
