#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int* a = (int*)malloc(sizeof(int) * 10);
    memset(a, 0, 10 * sizeof(int));
    int* b = (int*)malloc(sizeof(int) * 10);
    memcpy(b, a, 10 * sizeof(int));
    printf("Memory contents of a: ");
    for (int i = 0; i < 10; i++)
        printf("%d ", a[i]);
    free(a);
    printf("\nMemory contents of b: ");
    for (int j = 0; j < 10; j++)
        printf("%d ", b[j]);
    free(b);
}