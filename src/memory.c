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

void my_free(void* ptr)
{
    if(ptr==NULL) return;

    Block* block = (Block*)ptr-1;
    block->free = 1;

    merge_free_blocks();
}

void merge_free_blocks()
{
    Block* current = head;

    while(current != NULL && current->next!=NULL)
    {
        if(current->free && current->next->free)
        {
            current->size += sizeof(Block) + current->next->size;
            current->next = current->next->next;
        }
        else
        {
            current = current->next;
        }
    }


}

void print_memory_visual()
{
    Block* current = head;
    printf("Heap layout: \n");

    while(current != NULL)
    {
        printf("[H][%s:%zu]", current->free ? "FREE" : "USED", current->size);

        current=current->next;
    }
    printf("\n");
}

void print_memory_bar_advanced() {
    Block* current = head;

    printf("\nHeap layout (advanced view):\n");

    // status print (USED/FREE)
    while(current != NULL) {
        printf("[H:%s]", current->free ? "FREE" : "USED");
        current = current->next;
    }
    printf("\n");

    current = head;
    while(current != NULL) {
        int bar_length = current->size / 10; 
        if(bar_length == 0) bar_length = 1;

        char c = current->free ? '-' : '#';
        printf("  "); 
        for(int i = 0; i < bar_length; i++) {
            printf("%c", c);
        }

        current = current->next;
    }
    printf("\n\n");
}