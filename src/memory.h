#ifndef MEMORY_H
#define MEMORY_H

void init_memory();
void print_memory();
void* my_malloc(size_t size);
void my_free(void* ptr);
void merge_free_blocks();

#endif