#include <stdio.h>
#include <time.h>

int main(){
    int max;
    srand(time(NULL));
    scanf("%d", &max);
    printf("%d", ((rand() % (2*max)) - max));
}