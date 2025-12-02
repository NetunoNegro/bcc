// programa principal do projeto "The Boys - 2025/2"
// Autor: Pedro Henrique Dalazoana dos Passos, GRR 20251993


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "fprio.h"
#include "fila.h"
#include "entidades.h"
#include "eventos.h"

int main ()
{
  struct mundo m;
  srand(time(NULL));
  cria_mundo(&m);
  eventos_iniciais(&m);
  executa_mundo(&m);
  destroi_mundo(&m);
  fprio_destroi(m.lef);
  return (0) ;
}

