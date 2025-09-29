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

//soma o vetor na struct soma
struct racional soma_do_vetor(struct racional v[], int n){
  struct racional soma;
  int i;
  soma = cria_r(0, 1);
  for (i = 0; i <  n; i++){
    soma_r(soma, v[i], &soma);
  }
  return(soma);
}

//selection sort, tive que mudar a função compara_r pq divisão de 2 longs arredondava
void ordena_vetor(struct racional v[], int n){
  int i, j, menor;
  struct racional aux;
  for (i = 0; i < n ; i ++){
    menor = i;
    for (j = i + 1; j < n; j++){
      if (compara_r(v[j], v[menor]) == -1){
        menor = j;
      }
    }
    aux = v[i];
    v[i] = v[menor];
    v[menor] = aux;
  }
}

//vai do inicio até o fim vendo se tem NAN, quando encontra diminui o tamanho do vetor e vai pro fim do vetor e troca com o primeiro valido que encontrar,
//diminui o tamanho do vetor se encontrar NANs no final antes de encontrar um valido
void remove_nan(struct racional v[], int *n){
  int i, j;
  struct racional aux;
  for (i = 0; i < *n ; i++){
    if (!valido_r(v[i])){
      *n = *n - 1;
      for (j = *n ; j > i; j--){
        if (!valido_r(v[j])){
          *n = *n - 1;
        }
        if (valido_r(v[j])){
          aux = v[i];
          v[i] = v[j];
          v[j] = aux;
          break;
        }
      }
    }
  }
}

//imprime o vetor padrao exemplos
void imprime_vetor(struct racional v[], int n){
  int i;
  printf("VETOR = ");
  for (i = 0; i < n; i ++){
    imprime_r(v[i]);
  }
  printf("\n");
}

/* programa principal */
int main ()
{
  struct racional v[max];
  int n, i;
  scanf("%d", &n);
  if (n > 100 || n < 0){
    return(0);
  }
  //le vetor
  for (i = 0; i < n; i++){
    scanf("%ld %ld", &v[i].num, &v[i].den);
  }
  imprime_vetor(v, n);
  remove_nan(v, &n);
  imprime_vetor(v, n);
  ordena_vetor(v, n);
  imprime_vetor(v, n);
  printf("SOMA = ");
  imprime_r(soma_do_vetor(v, n));
  printf("\n");
  return (0);
}