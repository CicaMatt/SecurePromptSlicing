#include <stdio.h>
#include <stdlib.h>
int main(){
    int *a = (int*)malloc(sizeof(int)*5);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    a[3] = 4;
    a[4] = 5;
    int *b = (int*)malloc(sizeof(int)*5);
    b[0] = 6;
    b[1] = 7;
    b[2] = 8;
    b[3] = 9;
    b[4] = 10;
    printf("%d",b[0]);
    free(a);
    printf("%d",b[0]);
    free(b);
}