mymemory.h

// Estrutura que representa um bloco de memória alocado
typedef struct allocation {
    void *start;              // Um ponteiro para o início do bloco alocado
    size_t size;              // O tamanho da alocação
    struct allocation *next;  // Um ponteiro para a próxima allocation_t (para formar uma lista encadeada)
} allocation_t;

// Estrutura que representa o pool total de memória e todas as alocações atuais
typedef struct {
    void *pool;               // Um ponteiro para o início do bloco de memória total
    size_t total_size;        // O tamanho total do bloco de memória
    allocation_t *head;       // Um ponteiro para a primeira allocation_t (cabeça da lista encadeada)
} mymemory_t;
