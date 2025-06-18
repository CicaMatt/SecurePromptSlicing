#include<stdio.h>
int main(){
    int *a=(int*)malloc(sizeof(int));
    int *b=(int*)malloc(sizeof(int));
    *b=*a;
    printf("%d",*b);
    free(a);
    printf("%d",*b);
    free(b);
    return 0;
}