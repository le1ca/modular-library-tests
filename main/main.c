#include <stdio.h>
#include "module_table.h"
#include "module_manager.h"

int main(int argc, char **argv){
    module_init();
    module_load("./modules/foo-mod.so");
    module_call("foo_hello", 0);
    module_destroy();
    return 0;
}
