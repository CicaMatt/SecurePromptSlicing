#include <stdlib.h>

int main() {
    int buffer_size = 1024;
    char *buffer = malloc(buffer_size);
    free(buffer);
    return 0;
}