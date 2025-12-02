#include <stdio.h>
#include <stdlib.h>

#include "entidades.h"
#include "fprio.h"
#include "fila.h"
#include "eventos.h"
#include "imprime.h"

#define CHEGA 1
#define ESPERA 2
#define DESISTE 3
#define AVISA 4
#define ENTRA 5
#define SAI 6
#define VIAJA 7
#define MORRE 8
#define MISSAO 9
#define FIM 10

void insere_lef(struct mundo *m, int id1, int id2, int tipo, int tempo){
    struct item_evento *e = malloc(sizeof(struct item_evento));
    e->id1 = id1;
    e->id2 = id2;

    fprio_insere(m->lef, e, tipo, tempo);
}

void chega(struct mundo *m, int idheroi, int idbase){
    struct heroi h = m->herois[idheroi];
    struct base b = m->bases[idbase];
    int tempo = m->relogio;
    int espera;

    m->herois[idheroi].base_id = idbase;

    if (cjto_card(b.presentes) < b.lotacao && !fila_tamanho(b.fila_espera))
        espera = 1;
    else
        espera = (h.paciencia) > (10 * fila_tamanho(b.fila_espera));
    
    if (espera){
        insere_lef(m, idheroi, idbase, ESPERA, tempo);
        i_chega_fica(h, b, tempo);
    }
    else{
        insere_lef(m, idheroi, idbase, DESISTE, tempo);
        i_chega_sai(h, b, tempo);
    }
}

void espera(struct mundo *m, int idheroi, int idbase){
    struct heroi h = m->herois[idheroi];
    struct base b = m->bases[idbase];
    int tempo = m->relogio;

    i_espera(h, b, tempo);
    fila_insere(b.fila_espera, idheroi);
    if (fila_tamanho(b.fila_espera) > b.maior_fila)
        m->bases[idbase].maior_fila = fila_tamanho(b.fila_espera);
    insere_lef(m, idbase, -1, AVISA, tempo);
}

void desiste(struct mundo *m, int idheroi, int idbase){
    struct heroi h = m->herois[idheroi];
    struct base b = m->bases[idbase];
    int tempo = m->relogio;
    int base_dest = aleatorio(0, N_BASES - 1);

    insere_lef(m, idheroi, base_dest, VIAJA, tempo);
    i_desiste(h, b, tempo);
}

void avisa(struct mundo *m, int idbase){
    struct base b = m->bases[idbase];
    int id_heroi;
    int tempo = m->relogio;

    i_avisa(b, tempo);
    while (cjto_card(b.presentes) < b.lotacao && fila_tamanho(b.fila_espera) > 0){
        fila_retira(b.fila_espera, &id_heroi);
        cjto_insere(b.presentes, id_heroi);
        insere_lef(m, id_heroi, idbase, ENTRA, tempo);
        i_avisa_admite(id_heroi, b, tempo);
    }
}

void entra(struct mundo *m, int idheroi, int idbase){
    struct heroi h = m->herois[idheroi];
    struct base b = m->bases[idbase];
    int tempo = m->relogio;

    int TPB = 15 + h.paciencia * aleatorio(0, 20);
    insere_lef(m, idheroi, idbase, SAI, tempo + TPB);
    i_entra(h, b, tempo, tempo + TPB);
}

void sai(struct mundo *m, int idheroi, int idbase){
    struct heroi h = m->herois[idheroi];
    struct base b = m->bases[idbase];
    int tempo = m->relogio;

    cjto_retira(b.presentes, idheroi);
    int base_dest = aleatorio(0, N_BASES - 1);
    insere_lef(m, idheroi, base_dest, VIAJA, tempo);
    insere_lef(m, idbase, -1, AVISA, tempo);
    i_sai(h, b, tempo);
}

void viaja(struct mundo *m, int idheroi, int idbase){
    struct heroi h = m->herois[idheroi];
    int tempo = m->relogio;
    int b_atual = m->herois[idheroi].base_id;
    struct cordenada b_ini = m->bases[b_atual].local;
    struct cordenada b_dest = m->bases[idbase].local;

    int dis = distancia_cordenadas(b_ini ,b_dest);
    int duracao = dis / m->herois[idheroi].velocidade;

    insere_lef(m, idheroi, idbase, CHEGA, tempo + duracao);
    i_viaja(h, b_atual, idbase, dis, tempo + duracao, tempo);
}

void morre(struct mundo *m, int idheroi, int idmissao){
    int tempo = m->relogio;

    cjto_retira(m->bases[m->herois[idheroi].base_id].presentes, idheroi);
    m->herois[idheroi].vivo = 0;
    insere_lef(m, m->herois[idheroi].base_id, -1, AVISA, tempo);
    m->mortes++;
    i_morre(idheroi, idmissao, tempo);
}

void missao(struct mundo *m, int idmissao){
    struct base_dist v[N_BASES];
    struct missao mi = m->missoes[idmissao];
    int i, j, k;
    struct base base_perto;
    int tempo = m->relogio;
    int maior_xp;

    for (i = 0; i < N_BASES; i++){
        v[i].base = i;
        v[i].dist = distancia_cordenadas(mi.local, m->bases[i].local);
    }

    ordena(v);

    int BMP = 0;
    struct cjto_t *hab;
    int ids_herois[10];

    m->missoes[idmissao].tentativas++;
    if(m->maximo_tentativas < m->missoes[idmissao].tentativas)
        m->maximo_tentativas = m->missoes[idmissao].tentativas;
    i_missao(m->missoes[idmissao], tempo);
    for (i = 0; i < N_BASES; i++){
        base_perto = m->bases[v[i].base];
        hab = cjto_cria(N_HABILIDADES);
        k = 0;

        for (j = 0; j < N_HEROIS; j++){
            if(cjto_pertence(base_perto.presentes, j)){
                ids_herois[k] = j;
                k++;
            }
        }

        i_missao_teste(m->missoes[idmissao], base_perto.id, v[i].dist, base_perto.presentes ,tempo);
        
        for (j = 0; j < cjto_card(base_perto.presentes); j++){
            i_missao_heroi(m->missoes[idmissao], m->herois[ids_herois[j]], tempo);
        }

        for (j = 0; j < cjto_card(base_perto.presentes); j++){
            struct cjto_t *aux = hab;
            hab = cjto_uniao(hab, m->herois[ids_herois[j]].habilidades);
            cjto_destroi(aux);
        }
        i_missao_hab_t(m->missoes[idmissao], base_perto.id, hab, tempo);

        if (cjto_contem(hab, mi.hab_necessarias)){
            BMP = 1;
            break;
        }
        else if (i + 1 == N_BASES){
            BMP = 0;
            break;
        }
        cjto_destroi(hab);
    }

    if (BMP){
        m->missoes[idmissao].concluida = 1;
        m->bases[base_perto.id].missoes_feitas++;
        m->missoes_cumpridas++;
        for (i = 0; i < cjto_card(base_perto.presentes); i++){
           m->herois[ids_herois[i]].xp++;
        }
        i_missao_feita(m->missoes[idmissao], base_perto.id, hab ,tempo);
        cjto_destroi(hab);
        return;
    }
    else if(m->nCompostoV && (tempo % 2500 == 0)){
        m->nCompostoV--;
        m->missoes[idmissao].concluida = 1;
        int w = 0;
        k = 0;
        base_perto = m->bases[v[w].base];
            while(cjto_card(base_perto.presentes) == 0){
                w++;
                base_perto = m->bases[v[w].base];
            }
        for (j = 0; j < N_HEROIS; j++){
            if(cjto_pertence(base_perto.presentes, j)){
                ids_herois[k] = j;
                k++;
            }
        }
        cjto_destroi(hab);
        hab = cjto_cria(N_HABILIDADES);
        for (j = 0; j < cjto_card(base_perto.presentes); j++){
            struct cjto_t *aux = hab;
            hab = cjto_uniao(hab, m->herois[ids_herois[j]].habilidades);
            cjto_destroi(aux);
        }
        m->bases[base_perto.id].missoes_feitas++;
        m->missoes_cumpridas++;
        i_missao_feita(m->missoes[idmissao], base_perto.id, hab ,tempo);
        maior_xp = 0;
        for (i = 0; i < cjto_card(base_perto.presentes); i++){
            if (m->herois[ids_herois[i]].xp > m->herois[ids_herois[maior_xp]].xp)
                maior_xp = i;
        }
        insere_lef(m, ids_herois[maior_xp], idmissao, MORRE, tempo);
        for (i = 0; i < cjto_card(base_perto.presentes); i++){
            if (i != maior_xp){
                m->herois[ids_herois[i]].xp++;
            }
        }
        cjto_destroi(hab);
        return;
    }
    else{
        insere_lef(m, idmissao, -1, MISSAO, tempo + 1440);
        i_missao_impossivel(m->missoes[idmissao], tempo);
        cjto_destroi(hab);
        return;
    }
}


void eventos_iniciais(struct mundo *m){
    int i;
    int tempo, base;
    for (i = 0; i < N_HEROIS; i++){
        base = aleatorio(0, N_BASES - 1);
        tempo = aleatorio(0, 4320);
        insere_lef(m, m->herois[i].id, base, CHEGA, tempo);
    }
    for (i = 0; i < N_MISSOES; i++){
        tempo = aleatorio(0, T_FIM_DO_MUNDO);
        insere_lef(m, m->missoes[i].id, -1, MISSAO, tempo);
    }
    tempo = T_FIM_DO_MUNDO;
    insere_lef(m, -1, -1, FIM, tempo);
}

void executa_mundo(struct mundo *m){
    struct item_evento *e;
    int tempo, evento;

    while ((e = fprio_retira(m->lef, &evento, &tempo)) != NULL){

        if (evento < MISSAO && evento != AVISA){
            if(!m->herois[e->id1].vivo){
                free(e);
                continue;
            }
        }
        m->eventos_tratados ++;
        m->relogio = tempo;
        switch (evento){
            case CHEGA:
                chega(m, e->id1, e->id2);
                break;
            case ESPERA:
                espera(m, e->id1, e->id2);
                break;
            case DESISTE:
                desiste(m, e->id1, e->id2);
                break;
            case AVISA:
                avisa(m, e->id1);
                break;
            case ENTRA:
                entra(m, e->id1, e->id2);
                break;
            case SAI:
                sai(m, e->id1, e->id2);
                break;
            case VIAJA:
                viaja(m, e->id1, e->id2);
                break;
            case MORRE:
                morre(m, e->id1, e->id2);
                break;
            case MISSAO:
                missao(m, e->id1);
                break;
            case FIM:
                free(e);
                log_fim(m);
                return;
                break;
        }
    free(e);
    }
}


//a vibe é criar um struct com id de 2 coisas, que podem ser id de 1 heroi, 1 bases ou 1 missao (acho que nao precisa de 3)
//dai cria um ponteiro dessa struct e faz com que os itens dos nodos da lef sejam todas ela
//dai tipo quando precisar do item pega ele e usa id1 ou (id1 e id2)
//faz tipo - se tem so 1 coisa vai ser id1, se tiver 2 heroi e id1 sempre.
//a coisa e determinada por tipo no nodo da struct
//entao assim: na struct fpnodo (que vai ser tudo da lef) :
//void *item vai sempre ser ponteiro pra struct de 2 ids
//tipo vai ser o eventeo (1 é chega, 2 sei la, por ai vai)
//prio vai ser o relogio / tempo
//prox é proximo evento