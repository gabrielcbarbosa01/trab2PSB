#ifndef MYMEMORY_H
#define MYMEMORY_H

#include <stddef.h> // para size_t

// Estrutura para representar uma alocação de memória
typedef struct allocation {
    void *start;              // Ponteiro para o início do bloco alocado
    size_t size;              // Tamanho da alocação
    struct allocation *next;  // Ponteiro para a próxima alocação (lista encadeada)
} allocation_t;

// Estrutura para representar o gerenciador de memória
typedef struct mymemory {
    void *pool;               // Ponteiro para o início do pool de memória
    size_t total_size;        // Tamanho total do pool de memória
    allocation_t *head;       // Ponteiro para a primeira alocação (cabeça da lista encadeada)
} mymemory_t;

// Protótipos das funções
mymemory_t* mymemory_init(size_t size);
void* mymemory_alloc(mymemory_t *memory, size_t size);
void mymemory_free(mymemory_t *memory, void *ptr);
void mymemory_display(mymemory_t *memory);
void mymemory_cleanup(mymemory_t *memory);
void mymemory_stats(mymemory_t *memory);

#endif // MYMEMORY_H
