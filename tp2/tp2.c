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
  return (0) ;
}
