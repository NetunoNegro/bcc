#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "extras.h"
#include "entidades.h"
#include "conjunto.h"

//selection sort para vetor de struct base
//ordena com base na distancia
//a distancia é a distancia da base até alguma missao
void ordena(struct base_dist v[]){
    struct base_dist aux;
    int i, j, menor;

    for(i = 0; i < N_BASES; i++){
        menor = i;
        for(j = i; j < N_BASES; j++){
            if(v[menor].dist > v[j].dist){
                menor = j;
            }
        }
        aux = v[menor];
        v[menor] = v[i];
        v[i] = aux;
    }
}

//cria cordenada
struct cordenada cria_cordenada(int x, int y){
    struct cordenada aux;
    aux.x = x;
    aux.y = y;
    return aux;
}

//devove distancia de cordenada
int distancia_cordenadas(struct cordenada a, struct cordenada b){
    int n = a.x -b.x;
    int m = a.y - b.y;
    return sqrt(n*n + m*m);
}

//numero aleatorio
int aleatorio(int min, int max){
    return (rand() % (max - min + 1) + min);
}