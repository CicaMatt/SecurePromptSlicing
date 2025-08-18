#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    size_t size = atoi(argv[1]);
    char *buffer = malloc(size);
    if (!buffer) return 1;
    memset(buffer, 0, size);
    fwrite(buffer, 1, size, stdout);
    free(buffer);
    return 0;
}