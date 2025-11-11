#include <stdio.h>
#include "fila.h"


int main(){
    struct fila_t *f;
    int item;
    fila_imprime(f);
    if (!fila_insere(f,3))
        printf("fila nao iniciada\n");
    fila_imprime(f);
    if (!fila_retira(f, &item))
        printf("fila nao iniciada\n");
    f = fila_cria();
    printf("tamanho = %d", fila_tamanho(f));
    fila_imprime(f);
    fila_insere(f, 5);
    fila_imprime(f);
    fila_retira(f, &item);
    printf("item = %d\n", item);
    fila_imprime(f);
    fila_insere(f, 2);
    fila_imprime(f);
    fila_insere(f, 12);
    fila_imprime(f);
    fila_insere(f, 20);
    fila_imprime(f);
    printf("tamanho = %d", fila_tamanho(f));
    fila_retira(f, &item);
    printf("item = %d\n", item);
    fila_imprime(f);
    printf("tamanho = %d", fila_tamanho(f));
    fila_retira(f, &item);
    fila_retira(f, &item);
    fila_retira(f, &item);
    fila_retira(f, &item);
    fila_retira(f, &item);
    fila_imprime(f);
    printf("tamanho = %d", fila_tamanho(f));
    fila_insere(f, 23);
    fila_imprime(f);
    printf("tamanho = %d", fila_tamanho(f));
    fila_destroi(f);
}