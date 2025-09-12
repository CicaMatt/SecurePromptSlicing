#include <stdlib.h>

int main() {
    int buffer_size = 1024;
    char *buffer;

    for (int i = 0; i < 10; i++) {
        buffer = (char *)malloc(buffer_size);
        if (buffer != NULL) {
            free(buffer);
        }
    }

    return 0;
}