/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "racional.h"

/* Retorna o numerador do racional r */
long numerador_r (struct racional r){
  return (r.num);
}

/* Retorna o denominador do racional r */
long denominador_r (struct racional r){
  return (r.den);
}

/* Cria um número racional com o numerador e denominador indicados. */
struct racional cria_r (long numerador, long denominador){
  struct racional r;
  r.num = numerador;
  r.den = denominador;
  return(r);
}

/* Retorna 1 se o racional r for válido ou 0 se for inválido.
 * Um racional é inválido se seu denominador for zero */
int valido_r (struct racional r){
  if ((r.den == 0)){
    return(0);
  }
  return(1);
}

/* retorna um número aleatório entre min e max, inclusive. */
long aleat (long min, long max)
{
  long a;
  a = min + rand() % (max+1 - min);
  return (a);
}

/* Máximo Divisor Comum entre a e b*/
long mdc (long a, long b)
{
    long min, max, resto;
    a = labs(a);
    b = labs(b);
    if (a < b){
        min = a;
        max = b;
    }
    else {
        min = b;
        max = a;
    }
    while (min != 0){
        resto = max % min;
        max = min;
        min = resto;
    }
    return(max);
}

/* Recebe um número racional e o simplifica.
 * Se r for inválido, devolve-o sem simplificar. */
struct racional simplifica_r (struct racional r)
{
  long div;
  if ((r.den == 0)){
    return(r);
  }
  if ((r.num == 0)){
    r.den = 1;
    return(r);
  }
  div = mdc(r.num, r.den);
  r.num = r.num / div;
  r.den = r.den / div;
  if (r.den < 0){
    r.num = -r.num;
    r.den = -r.den;
  }
  return(r);
}

/* Retorna um número racional aleatório na forma simplificada.
 * O numerador e o denominador devem ser inteiros entre min e max.*/
struct racional sorteia_r (long min, long max){
  struct racional r;
  long num, den;
  num = aleat(min, max);
  den = aleat(min, max);
  r = cria_r(num, den);
  r = simplifica_r(r);
  return(r);
}

/* Imprime um racional r, respeitando estas regras:
   - o racional deve ser impresso na forma simplificada;
   - não imprima espaços em branco e não mude de linha;
   - a saída deve ter o formato "num/den", a menos dos casos abaixo:
     - se o racional for inválido, deve imprimir a mensagem "INVALIDO";
     - se o numerador for 0, deve imprimir somente "0";
     - se o denominador for 1, deve imprimir somente o numerador;
     - se o numerador e denominador forem iguais, deve imprimir somente "1";
     - se o racional for negativo, o sinal "-" deve vir antes do numerador;
     - se numerador e denominador forem negativos, o racional é positivo. */
void imprime_r (struct racional r){
  r = simplifica_r(r);
  if (!valido_r(r)){
    printf("NaN ");
  }
  else if ((r.num == 0)){
    printf("0 ");
  }
  else if ((r.den == 1)){
    printf("%ld ", r.num);
  }
  else if ((r.num == r.den)){
    printf("1 ");
  }
  else{
    printf("%ld/%ld ", r.num, r.den);
  }
}

/* Compara dois racionais r1 e r2. Retorno: -2 se r1 ou r2 for inválido,
 * -1 se r1 < r2, 0 se r1 = r2 ou 1 se r1 > r2 */
int compara_r (struct racional r1, struct racional r2){
  r1 = simplifica_r(r1);
  r2 = simplifica_r(r2);
  if (!valido_r(r1) || !valido_r(r2)){
    return(-2);
  }
  else if (r1.num * r2.den < r2.num * r1.den){
    return(-1);
  }
  else if ((r1.den == r2.den) && (r1.num == r2.num)){
    return(0);
  }
  else
  return(1);
}

//r1 + r2. iguala as bases para somar, depois simplifica
int soma_r (struct racional r1, struct racional r2, struct racional *r3){
  if (!r3){
    return(0);
  }
  if (!valido_r(r1) || !valido_r(r2)){
    (*r3).num = 0;
    (*r3).den = 0;
    return(0);
  }
  (*r3).den = r1.den * r2.den;
  (*r3).num = r1.num * r2.den + r2.num * r1.den;
  *r3 = simplifica_r(*r3);
  return(1);
}

//r1 - r2. iguala as bases para subtrair, depois simplifica.
int subtrai_r (struct racional r1, struct racional r2, struct racional *r3){
  if (!r3){
    return(0);
  }
  if (!valido_r(r1) || !valido_r(r2)){
    (*r3).num = 0;
    (*r3).den = 0;
    return(0);
  }
  (*r3).den = r1.den * r2.den;
  (*r3).num = r1.num * r2.den - r2.num * r1.den;
  (*r3) = simplifica_r((*r3));
  return(1);
}

/* Retorna a multiplicacao dos racionais r1 e r2 no parametro *r3.
 * Retorna 1 se a operacao foi bem sucedida ou
 *         0 se r1 ou r2 for inválido ou se *r3 for nulo */
//r1 * r2.
int multiplica_r (struct racional r1, struct racional r2, struct racional *r3){
  if (!r3){
    return(0);
  }
  if (!valido_r(r1) || !valido_r(r2)){
    (*r3).num = 0;
    (*r3).den = 0;
    return(0);
  }
  (*r3).num = r1.num * r2.num;
  (*r3).den = r1.den * r2.den;
  *r3 = simplifica_r(*r3);
  return(1);
}

/* Retorna a divisao dos racionais r1 e r2 no parametro *r3.
 * Retorna 1 se a operacao foi bem sucedida ou
 *         0 se r1 ou r2 for inválido ou se *r3 for nulo */
int divide_r (struct racional r1, struct racional r2, struct racional *r3){
  if (!r3){
    return(0);
  }
  if (!valido_r(r1) || !valido_r(r2) || (r2.num == 0)){
    (*r3).num = 0;
    (*r3).den = 0;
    return(0);
  }
  (*r3).num = r1.num * r2.den;
  (*r3).den = r1.den * r2.num;
  *r3 = simplifica_r(*r3);
  return(1);
}

/* Mínimo Múltiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b)
{
  return((a * b) / mdc(a, b));
}