#include <stdio.h>
#include <stdlib.h>
int main()
{
    char *buf = malloc(sizeof(char)*1024);
    fgets(buf, 1024, stdin);
    printf("%s", buf);

    char *buf1 = malloc(sizeof(char)*1024);
    fgets(buf1, 1024, stdin);
    printf("%s", buf1);

    free(buf);
    free(buf1);
}