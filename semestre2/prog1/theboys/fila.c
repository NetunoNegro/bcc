#include <stdio.h>
#include <stdlib.h>
#include "fila.h"


// descreve um nodo da fila 
struct fila_nodo_t
{
	int item ;			// item associado ao nodo
	struct fila_nodo_t *prox;	// próximo nodo
};

// descreve uma fila 
struct fila_t
{
	struct fila_nodo_t *prim ;	// primeiro nodo da fila
	struct fila_nodo_t *fim;	// último nodo da fila
	int num ;			// número de itens na fila
} ;

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

}

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

// Retira o primeiro item da fila e o devolve
// Retorno: ponteiro para o item retirado ou NULL se fila vazia ou erro.
int *fila_retira (struct fila_t *f){
    if (f == NULL || f->prim == NULL || f->num == 0)
        return -1;
    int *item = f->prim->item;
    struct fila_nodo_t *aux = f->prim->prox;
    free(f->prim);
    f->prim = aux;
    return item;
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
    while (aux != f->fim){
        printf("%d", aux->item);
        aux = aux->prox;
    }
    printf("%d", aux->item);
    return;
}