#include <stdlib.h>

int main() {
    int buffer_size = 1024;
    char *buffer = malloc(buffer_size);
    if (buffer == NULL) return 1;

    for (int i = 0; i < 5; i++) {
        free(buffer);
    }

    return 0;
}