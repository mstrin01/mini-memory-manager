#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define HEAP_SIZE 1024

typedef struct Block {
    size_t size;
    int free;            // 1 = free, 0 = used
    struct Block* next;
} Block;

static char heap[HEAP_SIZE];
static Block* head = NULL;

// ===== INIT HEAP =====
void init_memory() {
    head = (Block*)heap;
    head->size = HEAP_SIZE - sizeof(Block);
    head->free = 1;
    head->next = NULL;
}

// ===== COUNT HEADERS =====
size_t count_headers() {
    Block* current = head;
    size_t total = 0;
    while(current) {
        total += sizeof(Block);
        current = current->next;
    }
    return total;
}

// ===== PRINT HEAP DEBUG =====
void print_memory_debug() {
    Block* current = head;
    size_t total_used = 0;
    size_t total_free = 0;

    printf("\n=== HEAP STATE ===\n");

    while(current) {
        void* header_addr = (void*)current;
        void* data_addr = (void*)(current + 1);
        void* end_addr = (void*)((char*)data_addr + current->size);

        printf("[0x%p - 0x%p] HEADER | size=%zu | %s | data_start=0x%p\n",
               header_addr, end_addr, current->size,
               current->free ? "FREE" : "USED",
               data_addr);

        if(current->free)
            total_free += current->size;
        else
            total_used += current->size;

        current = current->next;
    }

    printf("\nTOTAL: %zu | USED: %zu | FREE: %zu\n\n",
           total_used + total_free + count_headers(),
           total_used,
           total_free);
}

// ===== MALLOC =====
void* my_malloc(size_t size) {
    Block* current = head;

    while(current) {
        if(current->free && current->size >= size) {
            if(current->size >= size + sizeof(Block) + 1) {
                Block* new_block = (Block*)((char*)(current + 1) + size);
                new_block->size = current->size - size - sizeof(Block);
                new_block->free = 1;
                new_block->next = current->next;

                current->size = size;
                current->next = new_block;
            }
            current->free = 0;
            return (void*)(current + 1);
        }
        current = current->next;
    }
    return NULL; // nema dovoljno memorije
}

// ===== FREE =====
void my_free(void* ptr) {
    if(!ptr) return;

    Block* block_ptr = (Block*)ptr - 1;
    block_ptr->free = 1;

    // merge sa sljedećim blokom ako je slobodan
    if(block_ptr->next && block_ptr->next->free) {
        block_ptr->size += sizeof(Block) + block_ptr->next->size;
        block_ptr->next = block_ptr->next->next;
    }
}

// ===== REALLOC =====
void* my_realloc(void* ptr, size_t new_size) {
    if(!ptr) return my_malloc(new_size);

    Block* block_ptr = (Block*)ptr - 1;

    if(block_ptr->size >= new_size) {
        // trenutno block već dovoljno velik
        return ptr;
    } else {
        // alociraj novi block i kopiraj
        void* new_ptr = my_malloc(new_size);
        if(!new_ptr) return NULL;

        memcpy(new_ptr, ptr, block_ptr->size);
        my_free(ptr);
        return new_ptr;
    }
}