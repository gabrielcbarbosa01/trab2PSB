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

// Aloca um bloco de memória do tamanho especificado
void* mymemory_alloc(mymemory_t *memory, size_t size) {
    // Verifique se o tamanho da alocação não excede o tamanho total da memória
    if (size > memory->total_size) {
        return NULL;
    }

    char* free_space = (char*)memory->pool;

    // Encontre um espaço livre adequado no pool de memória
    allocation_t *new_alloc = (allocation_t*)malloc(sizeof(allocation_t));
    if (!new_alloc) {
        return NULL;
    }

    // Verifique se há espaço suficiente no pool para alocar o bloco
    if ((memory->total_size - (free_space - (char*)memory->pool)) < size) {
        free(new_alloc);
        return NULL;
    }

    // Atribua o endereço do espaço livre para a alocação
    new_alloc->start = free_space;
    new_alloc->size = size;
    allocation_t * current = //(allocation_t*)malloc(sizeof(allocation_t));
    current = memory ->head;
    if(current == NULL){
        memory -> head = new_alloc;
    }
    else{
        while(current -> next != NULL){
        current = current -> next;
    }
    current ->next = new_alloc;
    }
    memory -> pool = (char *)memory->pool + size ;
    

    // Atualize o ponteiro para o próximo espaço livre no pool de memória
    //free_space += size;

    return new_alloc->start;
}

void * mymemory_alloc_fist_fit(mymemory_t *memory, size_t size){
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
    



    allocation_t * current = //(allocation_t*)malloc(sizeof(allocation_t));
    current = memory ->head;
    if(current == NULL){
        memory -> head = new_alloc;
        new_alloc ->start = (char *)memory ->pool;
        return new_alloc->start;
    }
    else{
        if((int)((current->start )-(memory->pool)) != 0){
            if((size_t)((current->start )-(memory->pool)) >= new_alloc -> size){
                new_alloc -> next = current;
                memory ->head = new_alloc;
                new_alloc ->start = (char *)memory ->pool;
                return new_alloc->start;
            }

        }
        while(current -> next != NULL){
            if((size_t)(current ->next ->start - current ->start ) > current ->size){
                //printf("%zu\n",(size_t)(current ->next ->start - current ->start ) - current ->size);
                if(((size_t)(current ->next ->start - current ->start ) - current ->size) >= new_alloc->size){
                    new_alloc ->next = current ->next;
                    current -> next = new_alloc;
                    new_alloc -> start = (char *)current -> start + current -> size;
                    return new_alloc->start;
                }

            }
        current = current -> next;
    }
    if((size_t)(final - (char *)(current -> start) - current ->size) >= new_alloc ->size){
        current -> next = new_alloc;
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



// Libera a alocação apontada por ptr
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
            //free(current->start);
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
    size_t total_free = memory->total_size; // Simplificado, assume que toda a memória livre está contígua
    size_t largest_free_block = total_free; // Simplificado
    size_t free_fragments = 0; // Simplificado, assume que não há fragmentos

    allocation_t *current = memory->head;
    while (current != NULL) {
        total_allocations++;
        total_allocated += current->size;
        current = current->next;
    }
    total_free -= total_allocated; // Simplificado, não contabiliza fragmentação ou alinhamento
    
    printf("Inicio da memória: %p\n", (char*) memory->start_m);
    if(total_allocations == 2){
        printf("Diferença =  %d \n",(int)((memory ->head ->next ->start )- (memory->head ->start)));

    }
    printf("Total de alocações: %zu\n", total_allocations);
    printf("Total de memória alocada: %zu bytes\n", total_allocated);
    printf("Total de memória livre: %zu bytes\n", total_free);
    printf("Maior bloco livre: %zu bytes\n", largest_free_block);
    printf("Número de fragmentos livres: %zu\n", free_fragments);
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