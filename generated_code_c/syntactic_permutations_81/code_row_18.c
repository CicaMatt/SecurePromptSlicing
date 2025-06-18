#include <stdio.h>
#include <stdlib.h>
int main(void){
    int *p = (int *)malloc(sizeof(int) * 1024);
    char arr[10];
    scanf("%s", arr);
    for (int i = 0; i < 10; ++i)
        p[i] = arr[i];
    return 0;
}