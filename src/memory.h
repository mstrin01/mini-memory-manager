#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

void init_memory();
void print_memory_debug();
void* my_malloc(size_t);
void* my_realloc(void* ptr, size_t new_size );
void my_free(void* ptr);
void merge_free_blocks();
int count_headers();
void print_stats();

#endif