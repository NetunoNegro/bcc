#include <stdio.h>
#include <stdlib.h>
#include "conjunto.h"
#include "fila.h"
#include "fprio.h"

struct cordenada{
    int x;
    int y;
};

struct heroi{
    int id;
    struct cjto_t habilidades;
    int paciencia;
    int velocidade;
    int xp;
    int base_id;
};

struct base{
    int id;
    int lotacao;
    struct cjto_t presentes;
    struct fila_t fila_espera;
    struct cordenada local;
};

struct missao{
    int id;
    struct cjto_t hab_necessarias;
    struct cordenada local;
};