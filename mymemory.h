#ifndef MYMEMORY_H
#define MYMEMORY_H

#include <stddef.h> // for size_t

typedef struct allocation {
    void *start;              // Pointer to the start of the allocated block
    size_t size;              // Size of the allocation
    struct allocation *next;  // Pointer to the next allocation (linked list)
} allocation_t;

typedef struct mymemory {
    void *pool;               // Pointer to the start of the memory pool
    size_t total_size;        // Total size of the memory pool
    allocation_t *head;       // Pointer to the first allocation (linked list head)
} mymemory_t;

// Function prototypes
mymemory_t* mymemory_init(size_t size);
void* mymemory_alloc(mymemory_t *memory, size_t size);
void mymemory_free(mymemory_t *memory, void *ptr);
void mymemory_display(mymemory_t *memory);
void mymemory_cleanup(mymemory_t *memory);
void mymemory_stats(mymemory_t *memory);

#endif // MYMEMORY_H
