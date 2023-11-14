#include "mymemory.h"
#include <stdio.h>

// gcc -o mymemory_program mymemory.c main.c 
// ./mymemory_program

int main() {
    // Inicializa o gerenciador de memória com um pool de 1024 bytes
    mymemory_t* my_memory = mymemory_init(1024);
    if (!my_memory) {
        printf("Falha ao inicializar o gerenciador de memória.\n");
        return 1;
    }

    // Exibe as estatísticas iniciais de memória
    printf("Estatísticas iniciais de memória:\n");
    mymemory_stats(my_memory);

    // Aloca alguma memória
    void* block1 = mymemory_alloc(my_memory, 100);
    if (!block1) {
        printf("Falha ao alocar o bloco de memória 1.\n");
        mymemory_cleanup(my_memory);
        return 1;
    }

    void* block2 = mymemory_alloc(my_memory, 256);
    if (!block2) {
        printf("Falha ao alocar o bloco de memória 2.\n");
        mymemory_free(my_memory, block1); // Libera o primeiro bloco se a segunda alocação falhar
        mymemory_cleanup(my_memory);
        return 1;
    }

    // Exibe a memória após as alocações
    printf("\nMemória após as alocações:\n");
    mymemory_display(my_memory);
    mymemory_stats(my_memory);

    // Libera um bloco de memória
    printf("\nLiberando o bloco 1...\n");
    mymemory_free(my_memory, block1);

    // Exibe a memória após a operação de liberação
    printf("\nMemória após liberar o bloco 1:\n");
    mymemory_display(my_memory);
    mymemory_stats(my_memory);

    // Limpa toda a memória
    printf("\nLimpando toda a memória...\n");
    mymemory_cleanup(my_memory);

    printf("Operações de gerenciamento de memória concluídas.\n");

    return 0;
}
