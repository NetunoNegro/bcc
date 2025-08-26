#include <stdio.h>

int main(){
    int a, b, min, max, resto, mmc;
    scanf("%d %d", &a, &b);
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
    printf("%d ", max);
    mmc = (a * b) / max;
    printf("%d ", mmc);
    a = a/max;
    b = b/max;
    printf("%d %d", a, b);
    return(0);
}