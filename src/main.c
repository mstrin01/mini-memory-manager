#include <stdio.h>
#include "memory.h"

int main()
{
    init_memory();
    

    void* a = my_malloc(100);
    void* b = my_malloc(50);

    print_memory();

    printf("FREEING FIRST BLOCK...\n");

    my_free(a);
    print_memory();

    return 0;
}