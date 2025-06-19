#include <stdio.h>
#include <stdlib.h>
int main(){
    int *mem1 = (int *) malloc(sizeof(int));
    int *mem2 = (int *) malloc(sizeof(int));
    memcpy(mem2,mem1, sizeof(int));
    printf("%d",*mem2);
    free(mem1);
    printf("%d",*mem2);
    free(mem2);
}