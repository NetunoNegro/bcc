#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    struct lista *l = malloc(sizeof(struct lista));
    if (l == NULL)
        return NULL;
    memset (l , 0, sizeof(struct lista));
    return l;
}

void lista_destroi (struct lista **lista){
    free(lista);
}

int lista_insere_inicio (struct lista *lista, int chave){
    struct nodo *n = malloc(sizeof(struct nodo));
    if (n == NULL || lista == NULL)
        return 0;
    n->chave = chave;
    n->prox = lista->ini;
    lista->ini = n;
    lista->tamanho++;
    return 1;
}

int lista_insere_fim (struct lista *lista, int chave){
    struct nodo *n = malloc(sizeof(struct nodo));
    if (n == NULL  || lista == NULL)
        return 0;
    n->chave = chave;
    struct nodo *aux = lista->ini;
    if (aux == NULL)
        return 0;
    while (aux->prox != NULL)
        aux = aux->prox;
    aux->prox = n;
    n->prox = NULL;
    lista->tamanho++;
    return 1;
}

int lista_insere_ordenado (struct lista *lista, int chave){
    struct nodo *n = malloc(sizeof(struct nodo));
    if (n == NULL || lista == NULL)
        return 0;
    n->chave = chave;
    if (lista->ini->chave > chave){
        n->prox = lista->ini;
        lista->ini = n;
        lista->tamanho++;
        return 1;
    }
    struct nodo *aux = lista->ini;
    while (aux->prox->chave < chave && aux->prox != NULL)
        aux = aux->prox;
    if (aux->prox == NULL){
        aux->prox = n;
        n->prox = NULL;
        lista->tamanho++;
        return 1;
    }
    n->prox = aux->prox;
    aux->prox = n;
    lista->tamanho++;
    return 1;
}

int lista_remove_inicio (struct lista *lista, int *chave){
    if (lista->tamanho == 0)
        return 0;
    *chave = lista->ini->chave;
    struct nodo *aux = lista->ini->prox;
    free(lista->ini);
    lista->ini = aux;
    lista->tamanho--;
    return 1;
}

int lista_remove_fim (struct lista *lista, int *chave){
    if (lista->tamanho == 0)
        return 0;
    struct nodo *aux = lista->ini;
    while (aux->prox != NULL)
        aux = aux->prox;
    *chave = aux->chave;
    free(aux);
    lista->tamanho--;
    return 1;
}

int lista_remove_ordenado (struct lista *lista, int chave){
    if(lista->tamanho == 0)
        return 0;
    struct nodo *aux = lista->ini;
    if (lista->ini->chave == chave){
        aux = lista->ini->prox;
        free(lista->ini);
        lista->ini = aux;
        lista->tamanho--;
        return 1;
    }
    while (aux->prox->chave != chave)
        aux = aux->prox;
    struct nodo *aux2 = aux->prox;
    aux->prox = aux->prox->prox;
    free(aux2);
    lista->tamanho--;
    return 1;
}

int lista_vazia (struct lista *lista){
    if (lista->tamanho == 0)
        return 1;
    return 0;
}

int lista_tamanho (struct lista *lista){
    return(lista->tamanho);
}

int lista_pertence (struct lista *lista, int chave){
    struct nodo *aux = lista->ini;
    while (aux->chave != chave && aux->prox != NULL)
        aux = aux->prox;
    if (aux->chave == chave)
        return 1;
    return 0;
}

void lista_inicia_iterador (struct lista *lista){
    lista->ptr = lista->ini;
}

int lista_incrementa_iterador (struct lista *lista, int *chave){
    if (lista->ptr == NULL)
        return 0;
    *chave = lista->ptr->chave;
    lista->ptr = lista->ptr->prox;
    return 1;
}
