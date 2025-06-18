c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int *mem1, *mem2;
    mem1 = (int *)malloc(50);
    mem2 = (int *)malloc(50);

    strcpy(mem2, mem1);
    printf("%s\n", mem2);
    free(mem1);
    printf("%s\n", mem2);
    free(mem2);
    return 0;
}