/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include "racional.h"
const int max = 100;
/* coloque aqui as funções auxiliares que precisar neste arquivo */


void ordena_vetor(struct racional v[], int n){
  
}

void remove_nan(struct racional v[], int *n){
  int i, j;
  struct racional aux;
  for (i = 0; i < *n ; i++){
    if (v[i].den == 0){
      *n = *n - 1;
      for (j = *n ; j > i; j--){
        if (v[j].den == 0){
          *n = *n - 1;
        }
        if (v[j].den != 0){
          aux = v[i];
          v[i] = v[j];
          v[j] = aux;
          break;
        }
      }
    }
  }
}


/* programa principal */
int main ()
{
  struct racional v[max];
  int n, i;
  scanf("%d", &n);
  for (i = 0; i < n; i++){
    scanf("%ld %ld", &v[i].num, &v[i].den);
  }
  printf("VETOR = ");
  for (i = 0; i < n; i ++){
    imprime_r(v[i]);
  }
  remove_nan(v, &n);
  printf("\nVETOR = ");
  for (i = 0; i < n; i ++){
    imprime_r(v[i]);
  }
  ordena_vetor(v, n);
  return (0);
}
