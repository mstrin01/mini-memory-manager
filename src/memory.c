#include <stdio.h>
#include "memory.h"

#define HEAP_SIZE 1024

static char heap[HEAP_SIZE];

typedef struct Block{
    size_t size; //size of data in bytes
    int free; //if free 1, if used 0
    struct Block* next;
}Block;

static Block* head = NULL;

void init_memory(){

    head = (Block*)heap;
    head->size = HEAP_SIZE - sizeof(Block); // [BLOCK][DATA] block is not used for data
    head->free = 1;
    head->next = NULL;

    printf("Heap initialized. Size: %d bytes\n",HEAP_SIZE);

}

void print_memory(){
    Block* current = head;
    
    while(current!=NULL){
        printf("Block size: %zu | %s \n", current->size, current->free ? "FREE" : "USED");

        current=current->next;
    }

}

void* my_malloc(size_t size){

    Block* current = head;

    while(current!=NULL)
    {
        if(current->size >= size+sizeof(Block)) {
            
            Block* new_block = (Block*)((char*)(current+1)+size);
            new_block->size = current->size - size - sizeof(Block);
            new_block->free = 1;
            new_block->next = current->next;

            current->size = size;
            current->next = new_block;

        }
        current->free = 0;

        return (void*)(current+1);

    }
    
    

}