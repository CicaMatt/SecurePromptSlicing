#include<stdio.h>
#include<stdlib.h>
int main()
{
    char* mem1 = (char*)malloc(sizeof(char)*10);
    char* mem2 = (char*)malloc(sizeof(char)*15);
    memcpy(mem2, mem1, 10*sizeof(char));
    printf("%s\n", mem2);
    free(mem1);
    printf("%s\n", mem2);
    free(mem2);
}