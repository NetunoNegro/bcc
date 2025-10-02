/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 09/09/2025 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"


/* coloque aqui as funções auxiliares que precisar neste arquivo */

//soma o vetor na struct *soma
void soma_do_vetor(struct racional **v, int n, struct racional *soma){
  int i;
  for (i = 0; i <  n; i++){
    soma_r(soma, v[i], soma);
  }
}

//selection sort
void ordena_vetor(struct racional **v, int n){
  int i, j, menor;
  struct racional *aux;
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

//remove os numeros invalidos, troca os invalidos mais pertos de v[0] pelos validos mais longe
//tambem remove os invalidos quando está buscando por um valido
void remove_nan(struct racional **v, int *n){
  int i, j;
  for (i = 0; i < *n; i++){
    if (!valido_r(v[i])){
      *n = *n - 1;
      destroi_r(&v[i]);
      for(j = *n; j > i; j--){
        if (!valido_r(v[j])){
          *n = *n - 1;
          destroi_r(&v[j]);
        }
        if (valido_r(v[j])){
          v[i] = v[j];
          v[j] = NULL;
          break;
        }
      }
    }
  }
}


//imprime o vetor no padrão
void imprime_vetor(struct racional **v, int n){
  int i;
  printf("VETOR =");
  if (n == 0)
    printf(" ");
  for (i = 0; i < n; i++){
    printf(" ");
    imprime_r(v[i]);
  }
  printf("\n");
}

//imprime a soma no padrão
void imprime_soma(struct racional *soma){
  printf("SOMA = ");
  imprime_r(soma);
  printf("\n");
}

//apaga os ponteiros do vetor
void apaga_valvetor(struct racional **v, int n){
  int i;
  for (i = 0; i < n; i++)
    destroi_r(&v[i]);
}

//le o vetor
void ler_vetor(struct racional **v, int n){
  int i;
  long num, den;
  for (i = 0; i < n; i++){
    scanf("%ld %ld", &num, &den);
    v[i] = cria_r(num, den);
  }
}

/* programa principal */
int main ()
{
  int n;
  struct racional *soma;
  scanf("%d", &n);
  if (n < 0 || n > 100)
    return 0;
  struct racional **vetor;
  vetor = malloc(n * sizeof(struct racional*));

  ler_vetor(vetor, n);
  imprime_vetor(vetor, n);

  remove_nan(vetor, &n);
  imprime_vetor(vetor, n);

  ordena_vetor(vetor, n);
  imprime_vetor(vetor, n);

  soma = cria_r(0, 1);
  soma_do_vetor(vetor, n, soma);
  imprime_soma(soma);

  apaga_valvetor(vetor, n);
  imprime_vetor(vetor, n);

  free(vetor);
  vetor = NULL;
  destroi_r(&soma);

  return 0;
}