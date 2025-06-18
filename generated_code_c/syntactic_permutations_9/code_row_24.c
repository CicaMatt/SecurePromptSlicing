#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv)
{
    if (argc <= 2)
    {
        printf("Please provide an index\n");
        return -1;
    }
    int idx = atoi(argv[1]);
    if (idx < 0 || idx >= argc)
    {
        printf("Index out of range\n");
        return -2;
    }
    char *arg = strdup(argv[idx + 1]);
    printf("Argument at index %d: %s\n", idx, arg);
    free(arg);
    return 0;
}