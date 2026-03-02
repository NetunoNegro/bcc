#include <stdio.h>
#include <stdlib.h>

struct deque{
    int tam;
    struct nodo *prim;
    struct nodo *ult;
};

struct nodo{
    int valor;
    struct nodo *prox;
    struct nodo *antes;
};

void insereInicio(struct deque *d, struct nodo *novo){
    if (d->prim == NULL && d->ult == NULL){
        d->prim = novo;
        d->ult = novo;
    }
    else{
        d->prim->antes = novo;
        novo->prox = d->prim;
        d->prim = novo;
    }
    d->tam++;
}

void insereFim(struct deque *d, struct nodo *novo){
    if (d->ult == NULL && d->prim == NULL){
        d->ult = novo;
        d->prim = novo;
    }
    else {
        d->ult->prox = novo;
        novo->antes = d->ult;
        d->ult = novo;
    }
    d->tam++;
}

struct nodo *removeInicio(struct deque *d){
    if (d == NULL || d->prim == NULL)
        return NULL;
    struct nodo *aux = d->prim->prox;
}

struct nodo *removeFim(struct deque *d){
    if (d == NULL || d->prim == NULL)
        return NULL;

}

int tamanho (struct deque *d){
    return (d->tam);
}

struct nodo *primeiro(struct deque *d){
    return (d->prim);
}

struct nodo *ultimo (struct deque *d){
    return (d->ult);
}

struct nodo *crianodo(int a){
    struct nodo *n = malloc(sizeof(struct nodo));
    n->antes = NULL;
    n->prox = NULL;
    n->valor = a;
    return n;
}

int main(){
    struct deque *d = malloc(sizeof(struct deque));

}