#include <stdlib.h>
int main()
{
    int* a = malloc(sizeof(int) * 5);
    for (int i=0; i<5; ++i)
        a[i] = i;
    
    int* b = malloc(sizeof(int) * 10);
    memcpy(b,a,sizeof(int)*5);
    free(a);
    
    for (int i=0; i<5; ++i)
        printf("%d\n", b[i]);
    return 0;
}