#ifndef ENTIDADES
#define ENTIDADES

#include "fila.h"
#include "fprio.h"
#include "extras.h"
#include "conjunto.h"


//defines iniciais propostos pelo pdf do trabalho
#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS N_HABILIDADES * 5
#define N_BASES N_HEROIS / 5
#define N_MISSOES T_FIM_DO_MUNDO / 100
#define N_COMPOSTOS_V N_HABILIDADES * 3
#define TAM_MUNDO 20000

//struct heroi
//id representa seu numero, entre 0 e N_HEROIS-1, seu "nome"
//habilidades é um conjunto de numeros, entre 0 e 9 (vem do N_HABILIDADES)
//define se o heroi consegue fazer missao ou nao, maximo 3 minimo 1
//paciencia modifica o tempo que fica na base e se aceita esperar filas
//veloidade serve para viajens, quando mais rapido, menor tempo de viajem
//xp sao quantas missoes ele fez
//base_id é o id da base que ele está no momento
//vivo = 1, se vivo = 0, heroi morto
struct heroi{
    int id;
    struct cjto_t *habilidades;
    int paciencia;
    int velocidade;
    int xp;
    int base_id;
    int vivo;
};

//struct base
//id representa seu numero, entre 0 e N_BASES -1, seu "nome"
//lotação representa a capacidade maxima de herois
//presentes representa os herois que ocupam a base no momento
//fila representa os herois que estao aguardando entrar na base
//local é a posição da base em um plano cartesiano
//missoes feitas é quantas missoes feitas a base participou
//maior fila é a maior fila que a base teve na execução do programa
struct base{
    int id;
    int lotacao;
    struct cjto_t *presentes;
    struct fila_t *fila_espera;
    struct cordenada local;
    int missoes_feitas;
    int maior_fila;
};


//struct missao
//id representa seu numero, entre 0 e N_MISSOES-1, seu "nome"
//habilidades necessárias são as habilidades que os herois, em conjunto da base
//precisam ter
//local é a posição da missao no plano cartesiano
//tentativas sao quantas vezes tentaram fazer a missao
//concluida é se foi feita
struct missao{
    int id;
    struct cjto_t *hab_necessarias;
    struct cordenada local;
    int tentativas;
    int concluida;
};

//struct mundo
//nHerois é a quantidade de herois (mortos ou vivos)
//herois[] é um vetor da struct heroi com tamanho N_HEROIS
//representa todos os herois do mundo
//nBases é a quantidade de bases
//bases[] é um vetor da struct base com tamanho N_BASES
//representa todas as bases do mundo
//nMissoes é a quantidade de missões do mundo
//missoes[] é um vetor da struct missao com tamanho N_MISSOES
//representa todas as missoes do mundo
//nHabilidades são quantos poderes existem
//nCompostoV quantos compostos existem
//tamanho é o tamanho máximo do mundo, todas as missoes e bases sao dentro dele
//relogio é o tempo do mundo
//lef é a fila de prioridades usada na execução dos eventos
//mortes sao quantas mortes teve
//eventos tratados quantos eventos ocorreram
//missoes cumpridas quantas missoes cumpridas
//minimo tentativas é o minimo de tentativas que os herois tiveram pra fazer 1 missao
//maximo tentativas o maximo de tentativas que os herois tiveram pra fazer 1 missao
struct mundo{
    int nHerois;
    struct heroi herois[N_HEROIS];
    int nBases;
    struct base bases[N_BASES];
    int nMissoes;
    struct missao missoes[N_MISSOES];
    int nHabilidades;
    int nCompostoV;
    struct cordenada tamanho;
    int relogio;
    struct fprio_t *lef;
    int mortes;
    int eventos_tratados;
    int missoes_cumpridas;
    int minimo_tentativas;
    int maximo_tentativas;
};

//inicia as missoes nos padroes do trabalho (vetor do mundo)
//onde acontece e as habilidades necssárias, por ex
void inicia_missoes(struct missao m[]);

//inicia as bases nos padroes do trabalho (vetor do mundo)
//lugar, lotação, inicia o cojunto dos presentes e fila de espera, por ex
void inicia_bases(struct base b[]);

//inicia os herois nos padroes do trabalho (vetor do mundo)
//decide o conjunto de habilidades, paciencia, velocidade, por ex
void inicia_heroi(struct heroi h[]);

//cria o mundo
//faz o setup dos vetores de missoes, bases e herois, por ex
void cria_mundo(struct mundo *m);

//libera os alocamentos de memórias criado em cria_mundo, menos da lef
void destroi_mundo(struct mundo *m);

#endif