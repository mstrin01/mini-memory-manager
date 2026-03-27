#include <stdio.h>
#include "memory.h"

int main()
{
    init_memory();
    

    void* a = my_malloc(100);
    void* b = my_malloc(50);

    print_memory_bar_advanced();

    printf("\n...FREEING FIRST BLOCK...\n");

    my_free(a);
    my_free(b);
    print_memory_bar_advanced();

    return 0;
}