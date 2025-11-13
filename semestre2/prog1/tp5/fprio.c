// TAD Fila de prioridades (FPRIO) genérica
// Carlos Maziero, DINF/UFPR, Out 2024
// Marcos Castilho, inclui as structs no arquivo.c, Out 2025
// Implementação com lista encadeada simples
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fprio.h"

// descreve um nodo da fila de prioridades
// NAO altere estas estruturas
struct fpnodo_t
{
  void *item ;          // item associado ao nodo
  int   tipo ;          // tipo do item
  int   prio ;          // prioridade do item
  struct fpnodo_t *prox;    // próximo nodo
};

// descreve uma fila de prioridades
struct fprio_t
{
  struct fpnodo_t *prim ;   // primeiro nodo da fila
  int num ;         // número de itens na fila
} ;

// A COMPLETAR

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

struct fprio_t *fprio_cria (){
  struct fprio_t *fila = malloc(sizeof(struct fprio_t));
  if (!fila)
    return NULL;
  memset (fila, 0, sizeof(struct fprio_t));
  return fila;
}

// Libera todas as estruturas de dados da fila, inclusive os itens.
// Retorno: NULL.
struct fprio_t *fprio_destroi (struct fprio_t *f){
  struct fpnodo_t *aux = f->prim;
  if (f == NULL)
    return NULL;
  while (aux != NULL){
    f->prim = f->prim->prox;
    free(aux);
    aux = f->prim;
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
  free (aux);
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
  struct fpnodo_t *aux = f->prim;
  while (aux != NULL){
    if (aux->prox == NULL)
      printf("(%d %d)", aux->tipo, aux->prio);
    else
      printf("(%d %d) ", aux->tipo, aux->prio);
    aux = aux->prox;
  }
}


