#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char* first = malloc(50);
    strcpy(first, "Hello, world!");

    char* second = malloc(50);
    memcpy(second, first, 50);

    printf("%s\n", second);

    free(first);
    free(second);

    return 0;
}