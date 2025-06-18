#include <stdio.h>
#include <stdlib.h>
int main() {
    char *first = malloc(10);
    strcpy(first, "abcdefgh");
    char *second = malloc(10);
    strcpy(second, first);
    printf("%s\n", second);
    free(first);
    printf("%s\n", second);
    free(second);
    return 0;
}