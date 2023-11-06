#ifndef MYMEMORY_H
#define MYMEMORY_H

// Ensure that size_t is only defined if it's not already defined
#ifndef SIZE_T_DEFINED
typedef unsigned long size_t;
#define SIZE_T_DEFINED
#endif

// Structure representing an allocated memory block
typedef struct allocation {
    void *start;              // Pointer to the start of the allocated block
    size_t size;              // Size of the allocation
    struct allocation *next;  // Pointer to the next allocation_t (to form a linked list)
} allocation_t;

// Structure representing the total memory pool and all current allocations
typedef struct mymemory {
    void *pool;               // Pointer to the start of the total memory block
    size_t total_size;        // Total size of the memory block
    allocation_t *head;       // Pointer to the first allocation_t (head of the linked list)
} mymemory_t;

#endif // MYMEMORY_H
