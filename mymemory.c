#include "mymemory.h"
#include <stdlib.h>
#include <stdio.h>

// Inicializa o gerenciador de memória com um tamanho especificado
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
    memory ->start_m = (char *) memory -> pool;
    return memory;
}


void* mymemory_alloc(mymemory_t *memory, size_t size) { 
    //escolhemos o first fit pois era o método mais "custo-benefício" de todos em relação a eficiência x complexidade



     // Verifique se o tamanho da alocação não excede o tamanho total da memória
    if (size > memory->total_size) {
        return NULL;
    }

    // EInicializa a estrutura allocation_t
    allocation_t *new_alloc = (allocation_t*)malloc(sizeof(allocation_t));
    if (!new_alloc) {
        return NULL;
    }


    //verificação se existe um fragmento de memória que seja capaz de armazenar o novo bloco
    new_alloc->size = size;
    int count = 0;
    char * final = (char *)memory->pool + memory->total_size;
    //printf("%p\n",final);
    allocation_t * verifica = memory->head;
    if(verifica != NULL){
        if((size_t)((verifica->start )-(memory->pool)) >= new_alloc ->size){
            count ++;
        }
        while(verifica -> next != NULL){
            if(((size_t)(verifica ->next ->start - verifica ->start ) - verifica ->size) >= new_alloc->size){
                count ++;
            }
            verifica = verifica ->next;
        }
        //printf("%zu\n",(size_t)(final - (char *)(verifica -> start) - verifica ->size) );
        if((size_t)(final - (char *)(verifica -> start) - verifica ->size) >= new_alloc ->size){
            count ++;
        }
        if(count == 0){
            free(new_alloc);
            return NULL;
            //se não foi encontrado cancela a operação


        }
    }
    //fim da verificação
    

    allocation_t * current; //(allocation_t*)malloc(sizeof(allocation_t));
    //inicio da alocação
    current = memory ->head;
    //se a lista for vazia cai nesta etapa
    if(current == NULL){
        memory -> head = new_alloc;
        new_alloc ->start = (char *)memory ->pool;
        return new_alloc->start;
    }
    else{
        //printf("%d\n", (int)((current->start )-(memory->pool)));
        //esta etapa verifica e aloca o bloco caso seja encontrado espaço entre o início do pool e o nodo head
        if((size_t)((current->start )-(memory->pool)) != 0){
            if((size_t)((current->start )-(memory->pool)) >= new_alloc -> size){
                new_alloc -> next = current;
                memory ->head = new_alloc;
                new_alloc ->start = (char *)memory ->pool;
                return new_alloc->start;
            }

        }
        //esta etapa verifica e aloca o bloco caso seja encontrado espaço entre os nodos da lista
        while(current -> next != NULL){
            if((size_t)(current ->next ->start - current ->start ) >= current ->size){
                //printf("%zu\n",(size_t)(current ->next ->start - current ->start ) - current ->size);
                if(((size_t)(current ->next ->start - current ->start) - current ->size) >= new_alloc->size){
                    //printf("entrou");
                    new_alloc ->next = current ->next;
                    current -> next = new_alloc;
                    new_alloc -> start = (char *)current -> start + current -> size;
                    return new_alloc->start;
                }

            }
        current = current -> next;
    }
    //esta etapa verifica e aloca o bloco caso seja encontrado espaço entre o ultimo nodo e o final do pool
    if((size_t)(final - (char *)(current -> start) - current ->size) >= new_alloc ->size){
        //printf("entrou\n");
        current -> next = new_alloc;
        new_alloc -> next = NULL;
        new_alloc ->start = (char *)current -> start + current ->size;
        return new_alloc->start;
    }
    free(new_alloc);
    return NULL;
    
    }
    
    
    


    free(new_alloc);
    return NULL;

}

// desconsidere essa função, ela é idêntica a de cima
void * mymemory_alloc_first_fit(mymemory_t *memory, size_t size){
     // Verifique se o tamanho da alocação não excede o tamanho total da memória
    if (size > memory->total_size) {
        return NULL;
    }



    
    // Encontre um espaço livre adequado no pool de memória
    allocation_t *new_alloc = (allocation_t*)malloc(sizeof(allocation_t));
    if (!new_alloc) {
        return NULL;
    }


    
    new_alloc->size = size;
    int count = 0;
    char * final = (char *)memory->pool + memory->total_size;
    //printf("%p\n",final);
    allocation_t * verifica = memory->head;
    if(verifica != NULL){
        if((size_t)((verifica->start )-(memory->pool)) >= new_alloc ->size){
            count ++;
        }
        while(verifica -> next != NULL){
            if(((size_t)(verifica ->next ->start - verifica ->start ) - verifica ->size) >= new_alloc->size){
                count ++;
            }
            verifica = verifica ->next;
        }
        //printf("%zu\n",(size_t)(final - (char *)(verifica -> start) - verifica ->size) );
        if((size_t)(final - (char *)(verifica -> start) - verifica ->size) >= new_alloc ->size){
            count ++;
        }
        if(count == 0){
            free(new_alloc);
            return NULL;


        }
    }
    

    allocation_t * current; //(allocation_t*)malloc(sizeof(allocation_t));
    current = memory ->head;
    if(current == NULL){
        memory -> head = new_alloc;
        new_alloc ->start = (char *)memory ->pool;
        return new_alloc->start;
    }
    else{
        //printf("%d\n", (int)((current->start )-(memory->pool)));
        if((size_t)((current->start )-(memory->pool)) != 0){
            if((size_t)((current->start )-(memory->pool)) >= new_alloc -> size){
                new_alloc -> next = current;
                memory ->head = new_alloc;
                new_alloc ->start = (char *)memory ->pool;
                return new_alloc->start;
            }

        }
        while(current -> next != NULL){
            if((size_t)(current ->next ->start - current ->start ) >= current ->size){
                //printf("%zu\n",(size_t)(current ->next ->start - current ->start ) - current ->size);
                if(((size_t)(current ->next ->start - current ->start) - current ->size) >= new_alloc->size){
                    //printf("entrou");
                    new_alloc ->next = current ->next;
                    current -> next = new_alloc;
                    new_alloc -> start = (char *)current -> start + current -> size;
                    return new_alloc->start;
                }

            }
        current = current -> next;
    }
    if((size_t)(final - (char *)(current -> start) - current ->size) >= new_alloc ->size){
        //printf("entrou\n");
        current -> next = new_alloc;
        new_alloc -> next = NULL;
        new_alloc ->start = (char *)current -> start + current ->size;
        return new_alloc->start;
    }
    free(new_alloc);
    return NULL;
    
    }
    
    
    

    // Atualize o ponteiro para o próximo espaço livre no pool de memória
    //free_space += size;
    free(new_alloc);
    return NULL;

}




void mymemory_free(mymemory_t *memory, void *ptr) {
    allocation_t *current = memory->head;
    allocation_t *previous = NULL;
    //varre a lista em busca do endereço informado

    while (current != NULL) {
        if (current->start == ptr) {
            if (previous) {
                //remoção em qualquer caso tirando a head
                previous->next = current->next;
            } else {
                //remoção caso seja head
                memory->head = current->next;
            }
            //free(current->start);
            //fim do mallok
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

// Exibe todas as alocações atuais
void mymemory_display(mymemory_t *memory) {
    allocation_t *current = memory->head;
    //printf("Inicio da memória: %p\n", (char*) memory->start_m);
    while (current != NULL) {
        printf("Início da alocação: %p, tamanho: %zu\n", current->start, current->size);
        current = current->next;
    }
}

// Exibe estatísticas gerais da memória
void mymemory_stats(mymemory_t *memory) {
    size_t total_allocations = 0; 
    size_t total_allocated = 0; 
    size_t total_free = memory->total_size; 
    size_t largest_free_block = total_free; 
    int free_fragments = 0; 

    // conta quantos nodos existem na memória e a memoria alocada
    allocation_t *current = memory->head;
    while (current != NULL) {
        total_allocations++;
        total_allocated += current->size;
        current = current->next;
    }
    //calcula a memoria ainda disponivel
    total_free -= total_allocated;

    current = memory ->head;
    size_t maior_bloco = 0;
    char * final = (char *)memory->pool + memory->total_size;
    //verifica o maior bloco de memoria livre

    if(current != NULL){
        if((size_t)((current->start )-(memory->pool)) != 0){
            maior_bloco = (size_t)((current->start )-(memory->pool));
        }
        while(current -> next != NULL){
            if(((size_t)(current ->next ->start - current ->start ) - current ->size) > maior_bloco){
                maior_bloco = (size_t)(current ->next ->start - current ->start ) - current ->size;
            }
            current = current ->next;
        }
        //printf("%zu\n",(size_t)(final - (char *)(verifica -> start) - verifica ->size) );
        if((size_t)(final - (char *)(current -> start) - current ->size) > maior_bloco){
            maior_bloco = (size_t)(final - (char *)(current -> start) - current ->size);
        }
        largest_free_block = maior_bloco;
        
    }

    current = memory ->head;
    int n_f = 0;

    //verifica quantos fragmentos de memoria existem
    if(current != NULL){
        if((size_t)((current->start )-(memory->pool)) != 0){
            n_f++;
        }
        while(current -> next != NULL){
            if(((size_t)(current ->next ->start - current ->start ) - current ->size) != 0){
                n_f++;
            }
            current = current ->next;
        }
        //printf("%zu\n",(size_t)(final - (char *)(verifica -> start) - verifica ->size) );
        if((size_t)(final - (char *)(current -> start) - current ->size) != 0){
            n_f ++;
        }
        free_fragments = n_f;
        
    }
    else(free_fragments = 1);


    
     
    
    printf("Inicio da memória: %p\n", (char*) memory->start_m);
    printf("Total de alocações: %zu\n", total_allocations);
    printf("Total de memória alocada: %zu bytes\n", total_allocated);
    printf("Total de memória livre: %zu bytes\n", total_free);
    printf("Maior bloco livre: %zu bytes\n", largest_free_block);
    printf("Número de fragmentos livres: %d\n", free_fragments);
}

// Limpa todos os recursos
void mymemory_cleanup(mymemory_t *memory) {
    allocation_t *current = memory->head;
    while (current != NULL) {
        allocation_t *next = current->next;
        free(current);
        current = next;
    }
    free(memory);
}