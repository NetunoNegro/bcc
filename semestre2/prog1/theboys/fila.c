#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
struct fila_t *fila_cria (){
    struct fila_t *f = malloc(sizeof(struct fila_t));
    if (f == NULL)
        return NULL;
    memset(f, 0, sizeof(struct fila_t));
    return f;
}

// Libera todas as estruturas de dados da fila, inclusive os itens.
// Retorno: NULL.
struct fila_t *fila_destroi (struct fila_t *f){
    if (f == NULL)
        return NULL;
    struct fila_nodo_t *aux = f->prim;
    while(aux != NULL){
        f->prim = f->prim->prox;
        free(aux);
        aux = f->prim;
    }
    free(f);
    return NULL;
}
/*
static int item_repetido(struct fila_t *f, int *item){
    struct fila_nodo_t *aux = f->prim;
    while (aux != f->fim){
        if (aux->item == item)
            return 1;
        aux = aux->prox;
    }
    if (aux->item == item)
        return 1;
    return 0;
}

// Insere o item na fila
// Inserir duas vezes o mesmo item (o mesmo ponteiro) é um erro.
// Retorno: número de itens na fila após a operação ou -1 se erro.
int fila_insere (struct fila_t *f, int *item){
    if (f == NULL || item == NULL)
        return -1;
    if (item_repetido(f, item))
        return -1;
    struct fila_nodo_t *aux = malloc(sizeof(struct fila_nodo_t));
    aux->item = *item;
    if (f->num == 0){

    }
}
*/
// Insere um item no final da fila (politica FIFO).
// Retorno: 1 se tiver sucesso ou 0 se falhar.
int fila_insere (struct fila_t *f, int item){
    if (f == NULL)
        return 0;
    struct fila_nodo_t *aux = malloc(sizeof(struct fila_nodo_t));
    aux->item = item;
    aux->prox = NULL;
    if (f->num == 0){
        f->prim = aux;
        f->ult = aux;
        f->num++;
        return 1;
    }
    f->ult->prox = aux;
    f->ult = aux;
    f->num++;
    return 1;
}

// Retira o primeiro item da fila e o devolve
// Retorno 1 se a operação foi bem sucedida e 0 caso contrário
int fila_retira (struct fila_t *f, int *item){
    if (f == NULL || f->prim == NULL || f->num == 0)
        return 0;
    *item = f->prim->item;
    struct fila_nodo_t *aux = f->prim->prox;
    free(f->prim);
    f->prim = aux;
    f->num--;
    return 1;
}

// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fila_tamanho (struct fila_t *f){
    if (f == NULL)
        return -1;
    return f->num;
}

// Imprime o conteúdo da fila
void fila_imprime (struct fila_t *f){
    if (f == NULL || f->num == 0){
        printf("Fila vazia/não iniciada!\n");
        return;
    }
    struct fila_nodo_t *aux = f->prim;
    printf("Fila : ");
    while (aux != NULL){
        printf("%d ", aux->item);
        aux = aux->prox;
    }
    printf("\n");
    return;
}