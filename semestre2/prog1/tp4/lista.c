#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
/* coloque demais includes aqui */

/* ------------------- Nao altere estas structs ------------------------- */
struct nodo {
    int chave;
    struct nodo *prox;
};

struct lista {
    struct nodo *ini;
    struct nodo *ptr; /* ponteiro para algum nodo da lista (iterador) */
    int tamanho;

};
/* ---------------------------------------------------------------------- */

struct lista *lista_cria (){
    struct lista *l = malloc(2*sizeof(struct nodo) + sizeof(int));
    if (l == NULL)
        return NULL;
    l->tamanho = 0;
    l->ini = NULL;
    l->ptr = NULL;
    return l;
}

void lista_destroi (struct lista **lista){
}

int lista_insere_inicio (struct lista *lista, int chave){
    struct nodo *n = malloc(sizeof(int) + sizeof(struct nodo));
    if (n == NULL)
        return 0;
    n->chave = chave;
    n->prox = lista->ini;
    lista->ini = n;
    lista->tamanho++;
    return 1;
}

int lista_insere_fim (struct lista *lista, int chave){
    struct nodo *n = malloc(sizeof(int) + sizeof(struct nodo));
    if (n == NULL)
        return 0;
    n->chave = chave;
    int i;
    struct nodo *aux = lista->ini;
    for (i = 1; i < lista->tamanho; i++){
        aux = aux->prox;
    }
    aux->prox = n;
    n->prox = NULL;
    lista->tamanho++;
    return 1;
}

int lista_insere_ordenado (struct lista *lista, int chave){
}

int lista_remove_inicio (struct lista *lista, int *chave){
}

int lista_remove_fim (struct lista *lista, int *chave){
}

int lista_remove_ordenado (struct lista *lista, int chave){
}

int lista_vazia (struct lista *lista){
}

int lista_tamanho (struct lista *lista){
    return(lista->tamanho);
}

int lista_pertence (struct lista *lista, int chave){
}

void lista_inicia_iterador (struct lista *lista){
}

int lista_incrementa_iterador (struct lista *lista, int *chave){
}
