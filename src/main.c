#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

#define MAX_BLOCKS 100
#define HEAP_SIZE 1024


void menu() {
    printf(" === MEMORY MANAGER ===\n");
    printf("1. ALLOCATE\n");
    printf("2. FREE\n");
    printf("3. PRINT HEAP\n");
    printf("4. REALLOC\n");
    printf("5. EXIT\n");
    printf("Choose an option from 1 - 5: ");
}

int main() {
    init_memory();
    void* blocks[MAX_BLOCKS] = {NULL};
    int index_counter = 0;

    printf("Heap initialized. Size: %d bytes\n\n", HEAP_SIZE);

    int choice;
    do {
        menu();
        scanf("%d", &choice);

        if(choice == 1) { // ALLOCATE
            size_t size;
            printf("Enter size: ");
            scanf("%zu", &size);
            void* ptr = my_malloc(size);
            if(ptr) {
                blocks[index_counter] = ptr;
                printf("Allocated at index %d\n\n", index_counter);
                index_counter++;
            } else {
                printf("Allocation failed. Not enough memory.\n\n");
            }

        } else if(choice == 2) { // FREE
            int idx;
            printf("Enter index to free: ");
            scanf("%d", &idx);
            if(idx >= 0 && idx < index_counter && blocks[idx]) {
                my_free(blocks[idx]);
                blocks[idx] = NULL;
                printf("Freed.\n\n");
            } else {
                printf("Invalid index.\n\n");
            }

        } else if(choice == 3) { // PRINT
            print_memory_debug();

        } else if(choice == 4) { // REALLOC
            int idx;
            size_t new_size;
            printf("Enter index: ");
            scanf("%d", &idx);
            printf("Enter new size: ");
            scanf("%zu", &new_size);
            if(idx >=0 && idx < index_counter && blocks[idx]) {
                void* new_ptr = my_realloc(blocks[idx], new_size);
                if(new_ptr) {
                    blocks[idx] = new_ptr;
                    printf("Reallocated.\n\n");
                } else {
                    printf("Reallocation failed.\n\n");
                }
            } else {
                printf("Invalid index.\n\n");
            }

        } else if(choice == 5) { // EXIT
            printf("Exiting...\n");
        } else {
            printf("Invalid choice.\n\n");
        }

    } while(choice != 5);

    return 0;
}