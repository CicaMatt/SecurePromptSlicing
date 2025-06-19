#include <stdio.h>
#include <stdlib.h> // for dynamic memory allocation functions

int main()
{
    char *buf = malloc(1024);
    if (!buf) {
        printf("Memory Allocation Error\n");
        exit(EXIT_FAILURE);
    }
    fgets(buf, 1024, stdin);

    char *buf1 = malloc(1024);
    if (!buf1) {
        printf("Memory Allocation Error\n");
        exit(EXIT_FAILURE);
    }
    fgets(buf1, 1024, stdin);

    free(buf);
    free(buf1);

    return 0;
}