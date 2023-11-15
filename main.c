#include "mymemory.h"
#include <stdio.h>

// gcc -o mymemory_program mymemory.c main.c 
// ./mymemory_program

int main() {
// Inicializa o gerenciador de memória com um pool de 1024 bytes
mymemory_t* my_memory = mymemory_init(400);
if (!my_memory) {
printf("Falha ao inicializar o gerenciador de memória.\n");
return 1;
}

// Exibe as estatísticas iniciais de memória
printf("Estatísticas iniciais de memória:\n");
mymemory_stats(my_memory);
printf("\n");

void * block1 = mymemory_alloc(my_memory, 100);
void * block2 = mymemory_alloc(my_memory, 100);
void * block3 = mymemory_alloc(my_memory, 100);
mymemory_free(my_memory,block2);
void * block4 = mymemory_alloc(my_memory, 190);
mymemory_free(my_memory,block1);
void * block5 = mymemory_alloc(my_memory, 190);
void * block6 = mymemory_alloc(my_memory, 90);
mymemory_free(my_memory,block5);
void * block7 = mymemory_alloc(my_memory, 200);
void * block8 = mymemory_alloc(my_memory, 10);
mymemory_display(my_memory);
//printf("a\n");
mymemory_stats(my_memory);
mymemory_cleanup(my_memory);

return 0;
}
