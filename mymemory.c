#include "mymemory.h"
#include <stdlib.h>
#include <stdio.h>

// Initializes the memory manager with a specified size
mymemory_t* mymemory_init(size_t size) {
    mymemory_t* memory = (mymemory_t*)malloc(sizeof(mymemory_t));
    if (!memory) {
        return NULL;
    }
    memory->pool = malloc(size);
    if (!memory->pool) {
        free(memory);
        return NULL;
    }
    memory->total_size = size;
    memory->head = NULL;
    return memory;
}

// Allocates a block of memory of the specified size
void* mymemory_alloc(mymemory_t *memory, size_t size) {
    // This is a very simplified version without actual memory management logic
    // Normally, you would search through the linked list for a suitable space
    allocation_t *new_alloc = (allocation_t*)malloc(sizeof(allocation_t));
    if (!new_alloc) {
        return NULL;
    }
    new_alloc->start = malloc(size);
    if (!new_alloc->start) {
        free(new_alloc);
        return NULL;
    }
    new_alloc->size = size;
    new_alloc->next = memory->head;
    memory->head = new_alloc;
    return new_alloc->start;
}

// Frees the allocation pointed by ptr
void mymemory_free(mymemory_t *memory, void *ptr) {
    allocation_t *current = memory->head;
    allocation_t *previous = NULL;

    while (current != NULL) {
        if (current->start == ptr) {
            if (previous) {
                previous->next = current->next;
            } else {
                memory->head = current->next;
            }
            free(current->start);
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

// Displays all current allocations
void mymemory_display(mymemory_t *memory) {
    allocation_t *current = memory->head;
    while (current != NULL) {
        printf("Allocation start: %p, size: %zu\n", current->start, current->size);
        current = current->next;
    }
}

// Displays general memory statistics
void mymemory_stats(mymemory_t *memory) {
    size_t total_allocations = 0;
    size_t total_allocated = 0;
    size_t total_free = memory->total_size; // Simplified, assumes all free memory is contiguous
    size_t largest_free_block = total_free; // Simplified
    size_t free_fragments = 0; // Simplified, assumes no fragments

    allocation_t *current = memory->head;
    while (current != NULL) {
        total_allocations++;
        total_allocated += current->size;
        current = current->next;
    }
    total_free -= total_allocated; // Simplified, does not account for fragmentation or alignment

    printf("Total allocations: %zu\n", total_allocations);
    printf("Total allocated memory: %zu bytes\n", total_allocated);
    printf("Total free memory: %zu bytes\n", total_free);
    printf("Largest free block: %zu bytes\n", largest_free_block);
    printf("Number of free fragments: %zu\n", free_fragments);
}

// Cleans up all resources
void mymemory_cleanup(mymemory_t *memory) {
    allocation_t *current = memory->head;
    while (current != NULL) {
        allocation_t *next = current->next;
        free(current->start);
        free(current);
        current = next;
    }
    free(memory->pool);
    free(memory);
}
