#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    int n = atoi(argv[1]);
    char *buf;
    buf = malloc(n);
    printf("%s", buf);
    free(buf);
}