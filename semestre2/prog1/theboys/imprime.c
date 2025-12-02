#include <stdio.h>

#include "conjunto.h"
#include "entidades.h"
#include "imprime.h"

void i_chega_fica(struct heroi h, struct base b, int tempo){
    printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ESPERA\n", tempo, h.id, b.id, cjto_card(b.presentes), b.lotacao);
}

void i_chega_sai(struct heroi h, struct base b, int tempo){
    printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) DESISTE\n", tempo, h.id, b.id, cjto_card(b.presentes), b.lotacao);
}

void i_espera(struct heroi h, struct base b, int tempo){
    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", tempo, h.id, b.id, fila_tamanho(b.fila_espera));
}

void i_desiste(struct heroi h, struct base b, int tempo){
    printf("%6d: DESISTE HEROI %2d BASE %d\n", tempo, h.id, b.id);
}

void i_avisa(struct base b, int tempo){
    printf("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d) FILA [ ", tempo, b.id, cjto_card(b.presentes), b.lotacao);
    fila_imprime(b.fila_espera);
    printf("]\n");
}

void i_avisa_admite(int idheroi, struct base b, int tempo){
    printf("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n", tempo, b.id, idheroi);
}

void i_entra(struct heroi h, struct base b, int tempo, int sai){
    printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n", tempo, h.id, b.id, cjto_card(b.presentes), b.lotacao, sai);
}

void i_sai(struct heroi h, struct base b, int tempo){
    printf("%6d: SAI  HEROI %2d BASE %d (%2d/%2d)\n", tempo, h.id, b.id, cjto_card(b.presentes), b.lotacao);
}

void i_viaja(struct heroi h, int b_atual, int b_dest, int dis, int chega, int tempo){
    printf("%6d: VIAJA HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", tempo, h.id, b_atual, b_dest, dis, h.velocidade, chega);
}

void i_morre(int idheroi, int idmissao, int tempo){
    printf("%6d: MORRE  HEROI %2d MISSAO %d\n", tempo, idheroi, idmissao);
}

void i_missao(struct missao mi, int tempo){
    printf("%6d: MISSAO %d TENT %d HAB REQ: [ ", tempo, mi.id, mi.tentativas);
    cjto_imprime(mi.hab_necessarias);
    printf(" ]\n");
}

void i_missao_feita(struct missao mi, int baseid, struct cjto_t *hab, int tempo){
    printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ", tempo, mi.id, baseid);
    cjto_imprime(hab);
    printf(" ]\n");
}

void i_missao_impossivel(struct missao mi, int tempo){
    printf("%6d: MISSAO %d IMPOSSIVEL\n", tempo, mi.id);
}

void i_missao_teste(struct missao mi, int baseid, int dis, struct cjto_t *herois,int tempo){
    printf("%6d: MISSAO %d BASE %d DIST %d HEROIS [ ", tempo, mi.id, baseid, dis);
    cjto_imprime(herois);
    printf(" ]\n");
}

void i_missao_heroi(struct missao mi, struct heroi h, int tempo){
    printf("%6d: MISSAO %d HAB HEROI %2d: [ ", tempo, mi.id, h.id);
    cjto_imprime(h.habilidades);
    printf(" ]\n");
}

void i_missao_hab_t(struct missao mi, int idbase, struct cjto_t *hab_t, int tempo){
    printf("%6d: MISSAO %d UNIAO HAB BASE %d: [ ", tempo, mi.id, idbase);
    cjto_imprime(hab_t);
    printf(" ]\n");
}

void log_fim(struct mundo *m){
    int i;
    printf("%6d: FIM\n\n", m->relogio);
    for (i = 0; i < N_HEROIS; i++){
        if (m->herois[i].vivo){
            printf("HEROI  %2d VIVO  PAC %3d VEL %4d EXP %4d HABS [ ", i, m->herois[i].paciencia, m->herois[i].velocidade, m->herois[i].xp);
            cjto_imprime(m->herois[i].habilidades);
            printf(" ]\n");
        }
        else{
            printf("HEROI  %2d MORTO  PAC %3d VEL %4d EXP %4d HABS [ ", i, m->herois[i].paciencia, m->herois[i].velocidade, m->herois[i].xp);
            cjto_imprime(m->herois[i].habilidades);
            printf(" ]\n");
        }
    }
    printf("\n");
    for (i = 0; i < N_BASES; i++){
        printf("BASE  %2d LOT %2d FILA MAX %2d MISSOES %d\n", i, m->bases[i].lotacao, m->bases[i].maior_fila, m->bases[i].missoes_feitas);
    }
    printf("\n");


    int n_missoes = N_MISSOES;
    printf("EVENTOS TRATADOS: %d\n", m->eventos_tratados);
    float porcento = ((float)m->missoes_cumpridas / n_missoes) * 100;
    m->minimo_tentativas = m->missoes[0].tentativas;
    for (i = 1; i < n_missoes; i++)
        if(m->minimo_tentativas > m->missoes[i].tentativas)
            m->minimo_tentativas = m->missoes[i].tentativas;
    float media = 0.0;
    n_missoes = N_MISSOES;
    for (i = 0; i < n_missoes; i++)
        media = media + m->missoes[i].tentativas;
    media = media / n_missoes;
    printf("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n", m->missoes_cumpridas, n_missoes, porcento);
    printf("TENTATIVAS POR MISSAO: MIN %d, MAX %d, MEDIA %.1f\n", m->minimo_tentativas, m->maximo_tentativas, media);
    
    int n_herois = N_HEROIS;
    float taxa_mortalidade = (float)(m->mortes) / n_herois * 100;
    printf("TAXA MORTALIDADE: %.1f%%\n", taxa_mortalidade);
    printf("\n");
}
