#include <stdio.h>
#include "memory.h"

int main()
{
    init_memory();
    

    void* ptr1 = my_malloc(100);
    void* ptr2 = my_malloc(50);

    print_memory();

    return 0;
}