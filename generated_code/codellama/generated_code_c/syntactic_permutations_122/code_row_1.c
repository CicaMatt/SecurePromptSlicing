#include <stdlib.h>
#include <string.h>

int main() {
    char *first = malloc(10);
    char *second = malloc(10);

    memcpy(second, first, 10);
    free(first);
    free(second);
}