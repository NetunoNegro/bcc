#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fprio.h"

//verifica se o item já está na fila de prioridades
int item_repetido(struct fprio_t *f, void *item){
  if (f == NULL || item == NULL || f->num == 0)
    return 0;
  struct fpnodo_t *aux = f->prim;
  while (aux != NULL){
    if (aux->item == item)
      return 1;
    aux = aux->prox;
  }
  return 0;
}

// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
struct fprio_t *fprio_cria (){
    struct fprio_t *f = malloc(sizeof(struct fprio_t));
    if (f == NULL)
        return NULL;
    memset(f, 0, sizeof(struct fprio_t));
    return f;
}

// Libera todas as estruturas de dados da fila, inclusive os itens.
// Retorno: NULL.
struct fprio_t *fprio_destroi (struct fprio_t *f){
    if (f == NULL)
        return NULL;
    struct fpnodo_t *p;
    while (f->prim != NULL) {
        p = f->prim;
        f->prim = f->prim->prox;
        free(p->item);
        free(p);
    }
    free(f);
    return NULL;
}

// Insere o item na fila, mantendo-a ordenada por prioridades crescentes.
// Itens com a mesma prioridade devem respeitar a politica FIFO (retirar
// na ordem em que inseriu).
// Inserir duas vezes o mesmo item (o mesmo ponteiro) é um erro.
// Retorno: número de itens na fila após a operação ou -1 se erro.
int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio){
    if (f == NULL || item == NULL || item_repetido(f, item))
        return -1;
    struct fpnodo_t *n = malloc(sizeof(struct fpnodo_t));
    n->item = item;
    n->tipo = tipo;
    n->prio = prio;
    if (f->num == 0){
        f->prim = n;
        n->prox = NULL;
        f->num++;
        return f->num;
    }
    struct fpnodo_t *aux = f->prim;
    if (f->prim->prio > prio){
        n->prox = f->prim;
        f->prim = n;
        f->num++;
        return f->num;
    }
    while (aux->prox != NULL && aux->prox->prio <= prio){
        aux = aux->prox;
    }
    if (aux->prox == NULL){
        aux->prox = n;
        n->prox = NULL;
        f->num++;
        return f->num;
    }
    n->prox = aux->prox;
    aux->prox = n;
    f->num++;
    return f->num;
}

// Retira o primeiro item da fila e o devolve; o tipo e a prioridade
// do item são devolvidos nos parâmetros "tipo" e "prio".
// Retorno: ponteiro para o item retirado ou NULL se fila vazia ou erro.
void *fprio_retira (struct fprio_t *f, int *tipo, int *prio){
    if (f == NULL || tipo == NULL || prio == NULL || f->num == 0)
        return NULL;
    *tipo = f->prim->tipo;
    *prio = f->prim->prio;
    struct fpnodo_t *aux;
    void *item;
    aux = f->prim;
    f->prim = f->prim->prox;
    f->num--;
    item = aux->item;
    free(aux);
    return item;
}

// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fprio_tamanho (struct fprio_t *f){
    if (f == NULL)
        return -1;
    return f->num;
}

// Imprime o conteúdo da fila no formato "(tipo prio) (tipo prio) ..."
// Para cada item deve ser impresso seu tipo e sua prioridade, com um
// espaço entre valores, sem espaços antes ou depois e sem nova linha.
void fprio_imprime (struct fprio_t *f){
    if (f == NULL || f->num == 0)
        return;
    struct fpnodo_t *aux = f->prim;
    printf("(%d %d)", aux->tipo, aux->prio);
    aux = aux->prox;
    while (aux != NULL){
        printf(" (%d %d)", aux->tipo, aux->prio);
        aux = aux->prox;
    }
}