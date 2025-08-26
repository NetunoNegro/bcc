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
#include <math.h>
#include "racional.h"


/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
*/
struct racional soma_r (struct racional r1, struct racional r2){
  struct racional r3;
  if (r1.den != r2.den){
    r1.num = r1.num * r2.den;
    r1.den = r1.den * r2.den;
    r2.num = r2.num * r1.den;
    r2.den = r2.den * r1.den;
  }
  r3.den = r1.den;
  r3.num = r1.num + r2.num;
  r3 = simplifica_r(r3);
  return(r3);
}

struct racional subtrai_r (struct racional r1, struct racional r2){
  struct racional r3;
  if (r1.den != r2.den){
    r1.num = r1.num * r2.den;
    r1.den = r1.den * r2.den;
    r2.num = r2.num * r1.den;
    r2.den = r2.den * r1.den;
  }
  r3.den = r1.den;
  r3.num = r1.num - r2.num;
  r3 = simplifica_r(r3);
  return(r3);
}

struct racional multiplica_r (struct racional r1, struct racional r2){
  struct racional r3;
  r3.num = r1.num * r2.num;
  r3.den = r1.den * r2.den;
  r3 = simplifica_r(r3);
  return(r3);
}

struct racional divide_r (struct racional r1, struct racional r2){
  struct racional r3;
  r3.num = r1.num * r2.den;
  r3.den = r1.den * r2.num;
  r3 = simplifica_r(r3);
  return(r3);
}




/* retorna um número aleatório entre min e max, inclusive. */
long aleat (long min, long max)
{
  /* implemente aqui */
  
}

/* Máximo Divisor Comum entre a e b      */
/* calcula o MDC pelo método de Euclides */
long mdc (long a, long b)
{
    int min, max, resto;
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
  /* implemente aqui */
}

/* Mínimo Múltiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b)
{
  return((a * b) / mdc(a, b));
  /* implemente aqui */
}

/* Recebe um número racional e o simplifica.
 * Por exemplo, ao receber 10/8 deve retornar 5/4.
 * Se ambos numerador e denominador forem negativos, deve retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Se r for inválido, devolve-o sem simplificar. */
struct racional simplifica_r (struct racional r)
{
  if (r.den = 0){
    return(r);
  }
  r.num = r.num / mdc(r.num, r.den);
  r.den = r.den / mdc(r.num, r.den);
  
  if (r.den < 0){
    r.num = -r.num;
    r.den = -r.den;
  }

  return(r);
  /* implemente aqui */
}

/* implemente as demais funções aqui */