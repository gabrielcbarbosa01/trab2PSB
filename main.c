#include "mymemory.h"
#include <stdio.h>

int main() {
    int opc = 0;
    size_t numero;
    printf("Digite o tamanho da memória: ");
    scanf("%zu", &numero);

    // Inicializa o gerenciador de memória com o tamanho fornecido
    mymemory_t *my_memory = mymemory_init(numero);

    if (!my_memory) {
        printf("Falha ao inicializar o gerenciador de memória.\n");
        return 1;
    }

    do {
        printf("GERENCIADOR DE MEMÓRIA \n");
        printf("1) ALOCAÇÃO DE BLOCO DE MEMÓRIA\n");
        printf("2) DESALOCAÇÃO DE BLOCO DE MEMÓRIA\n");
        printf("3) LISTAR BLOCOS DE MEMÓRIA\n");
        printf("4) MOSTRAR INFORMAÇÕES DA MEMÓRIA\n");
        printf("5) SAIR DO SISTEMA\n");
        printf("-------------------------------------------------\n");
        printf("\n");

        scanf("%d", &opc);

        if (opc == 1) {
            printf("DIGA A QUANTIDADE DE BYTES QUE SERÃO ALOCADOS: ");
            scanf("%zu", &numero);
            void *bloco = mymemory_alloc_first_fit(my_memory, numero);
            if (bloco) {
                printf("Bloco alocado com sucesso.\n");
            } else {
                printf("Falha ao alocar bloco de memória.\n");
            }
            printf("-------------------------------------------------\n");
        } else if (opc == 2) {
            printf("DIGA O ENDEREÇO DO BLOCO QUE SERÁ DESALOCADO: \n");
            mymemory_display(my_memory);
            
    
            unsigned long endereco;  
            scanf("%lx", &endereco);
            void *bloco = (void*)endereco;

            mymemory_free(my_memory, bloco);
            printf("Bloco desalocado com sucesso.\n");
        } else if (opc == 3) {
            mymemory_display(my_memory);
            printf("-------------------------------------------------\n");
        } else if (opc == 4) {
            mymemory_stats(my_memory);
            printf("-------------------------------------------------\n");
        } else if (opc == 5) {
            printf("Saindo do sistema.\n");
        } else {
            printf("Opção inválida.\n");
        }

    } while (opc != 5);

    // Limpa todos os recursos antes de sair
    mymemory_cleanup(my_memory);

    return 0;
}
