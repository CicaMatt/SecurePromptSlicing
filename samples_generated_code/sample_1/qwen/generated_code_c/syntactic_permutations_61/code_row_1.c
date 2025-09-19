#include <stdlib.h>

int main() {
    while (1) {
        char *buffer = malloc(1024);
        if (buffer == NULL) {
            return 1;
        }
        free(buffer);
    }
    return 0;
}