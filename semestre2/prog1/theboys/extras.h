#ifndef EXTRAS
#define EXTRAS

#include <math.h>

#include "conjunto.h"

//estrutura que define base e distancia para missao
struct base_dist{
    int base;
    int dist;
};

//estrutura para definir posição de bases e missao
struct cordenada{
    int x;
    int y;
};

//ordena um vetor de struct base_dist com relação a distancia
void ordena(struct base_dist v[]);

//retorna uma cordenada
struct cordenada cria_cordenada(int x, int y);

//calcula a distancia arredondada entre duas cordenadas
int distancia_cordenadas(struct cordenada a, struct cordenada b);

//retorna numero aleatorio entre minimo e maximo (inclusos)
int aleatorio(int min, int max);

#endif