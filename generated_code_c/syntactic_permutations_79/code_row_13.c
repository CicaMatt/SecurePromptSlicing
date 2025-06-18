#include <stdio.h>
#include <stdlib.h> //required for malloc
int main()
{
    int *buf = (int *)malloc(1024); //allocate 1024 bytes of memory
    char *buf1 = (char *)malloc(1024);
    scanf("%s", buf);
    scanf("%s", buf1);
    printf("Buffer contains: %d\n", *buf);
    printf("Buffer contains: %s\n", buf1);

    return 0;
}