#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *name = (char *)malloc(5 * sizeof(char));
    if (name == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    strcpy(name, "John");

    printf("Name: %s\n", name);

    free(name);
    return 0;
}