#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "conjunto.h"
#include "fila.h"
#include "fprio.h"
#include "extras.h"
#include "entidades.h"

void inicia_missoes(struct missao m[]){
    int i;
    for (i = 0; i < N_MISSOES; i++){
        m[i].id = i;
        m[i].local = cria_cordenada(aleatorio(0, TAM_MUNDO - 1), aleatorio(0, TAM_MUNDO - 1));
        m[i].hab_necessarias = cjto_aleat(aleatorio(6,10), N_HABILIDADES);
        m[i].tentativas = 0;
        m[i].concluida = 0;
    }
}

void inicia_bases(struct base b[]){
    int i;
    for (i = 0; i < N_BASES; i++){
        b[i].id = i;
        b[i].local = cria_cordenada(aleatorio(0, TAM_MUNDO - 1), aleatorio(0, TAM_MUNDO - 1));
        b[i].lotacao = aleatorio(3, 10);
        b[i].presentes = cjto_cria(N_HEROIS);
        b[i].fila_espera = fila_cria();
        b[i].missoes_feitas = 0;
        b[i].maior_fila = 0;
    }
}

void inicia_heroi(struct heroi h[]){
    int i;
    for(i = 0; i < N_HEROIS; i++){
        h[i].id = i;
        h[i].habilidades = cjto_aleat(aleatorio(1, 3), N_HABILIDADES);
        h[i].paciencia = aleatorio(0, 100);
        h[i].velocidade = aleatorio(50, 5000);
        h[i].xp = 0;
        h[i].base_id = -1;
        h[i].vivo = 1;
    }
}

void cria_mundo(struct mundo *m){
    m->nHerois = N_HEROIS;
    inicia_heroi(m->herois);
    m->nBases= N_BASES;
    inicia_bases(m->bases);
    m->nMissoes = N_MISSOES;
    inicia_missoes(m->missoes);
    m->nHabilidades = N_HABILIDADES;
    m->nCompostoV = N_COMPOSTOS_V;
    m->tamanho.x = TAM_MUNDO;
    m->tamanho.y = TAM_MUNDO;
    m->relogio = T_INICIO;
    m->lef = fprio_cria();
    m->mortes = 0;
    m->eventos_tratados = 0;
    m->missoes_cumpridas = 0;
    m->minimo_tentativas = 0;
    m->maximo_tentativas = 0;
}

//desaloca memoria alocada ao criar mundo
void destroi_mundo(struct mundo *m){
    int i;
    for (i = 0; i < N_HEROIS; i++)
        cjto_destroi(m->herois[i].habilidades);
    for (i = 0; i < N_BASES; i++){
        cjto_destroi(m->bases[i].presentes);
        fila_destroi(m->bases[i].fila_espera);
    }
    for(i = 0; i < N_MISSOES; i++)
        cjto_destroi(m->missoes[i].hab_necessarias);
}