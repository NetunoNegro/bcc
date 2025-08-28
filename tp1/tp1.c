/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "racional.h"

/* programa principal */
int main ()
{
    int n, i;
    long max;
    struct racional r1, r2, soma, sub, mult, div;
    //srand (0); /* use assim, com zero */
    srand(0);
    scanf("%d %d", &n, &max);
    for (i = 1; i <= n; i++){
        printf("%d: ", i);
        r1 = sorteia_r(0, max);
        r2 = sorteia_r(0, max);
        imprime_r(r1);
        imprime_r(r2);
        if (!valido_r(r1) || !valido_r(r2)){
            printf("NUMERO INVALIDO");
            return(1);
        }
        soma = soma_r(r1, r2);
        sub = subtrai_r(r1, r2);
        mult = multiplica_r(r1, r2);
        div = divide_r(r1, r2);
        if (!valido_r(div)){
            printf("DIVISAO INVALIDA");
            return(1);
        }
        imprime_r(soma);
        imprime_r(sub);
        imprime_r(mult);
        imprime_r(div);
        printf("\n");
    }
    /* a completar! */
    return (0) ;
}