#include <stdlib.h>
int main() {
    int buffer_size = 8;
    unsigned char *buffer = malloc(buffer_size);
    for (int i = 0; i < 1024; ++i) {
        free(buffer);
        buffer = malloc(buffer_size);
    }
    return 0;
}