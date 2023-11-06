#include "mymemory.h"
#include <stdio.h>

// gcc -o mymemory_program mymemory.c main.c 
// ./mymemory_program

int main() {
    // Initialize the memory manager with a pool of 1024 bytes
    mymemory_t* my_memory = mymemory_init(1024);
    if (!my_memory) {
        printf("Failed to initialize memory manager.\n");
        return 1;
    }

    // Display initial memory stats
    printf("Initial memory stats:\n");
    mymemory_stats(my_memory);

    // Allocate some memory
    void* block1 = mymemory_alloc(my_memory, 128);
    if (!block1) {
        printf("Failed to allocate memory block 1.\n");
        mymemory_cleanup(my_memory);
        return 1;
    }

    void* block2 = mymemory_alloc(my_memory, 256);
    if (!block2) {
        printf("Failed to allocate memory block 2.\n");
        mymemory_free(my_memory, block1); // Free the first block if the second allocation fails
        mymemory_cleanup(my_memory);
        return 1;
    }

    // Display memory after allocations
    printf("\nMemory after allocations:\n");
    mymemory_display(my_memory);
    mymemory_stats(my_memory);

    // Free one block of memory
    printf("\nFreeing block 1...\n");
    mymemory_free(my_memory, block1);

    // Display memory after the free operation
    printf("\nMemory after freeing block 1:\n");
    mymemory_display(my_memory);
    mymemory_stats(my_memory);

    // Cleanup all memory
    printf("\nCleaning up all memory...\n");
    mymemory_cleanup(my_memory);

    printf("Memory management operations completed.\n");

    return 0;
}
