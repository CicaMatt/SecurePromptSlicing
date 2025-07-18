#include<stdio.h>
#include<stdlib.h>
int main(){
    int *first,*second;
    first=(int *)malloc(sizeof(int)*10);
    second=(int *)malloc(sizeof(int)*10);
    memcpy(second,first,10*sizeof(int));
    free(first);
    free(second);
    return 0;
}
