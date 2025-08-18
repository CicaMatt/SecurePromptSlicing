#include <stdlib.h>

int main() {
    char *buffer;
    int i;

    for (i = 0; i < 10; i++) {
        buffer = malloc(1024);
        if (buffer != NULL) {
            free(buffer);
        }
    }

    return 0;
}