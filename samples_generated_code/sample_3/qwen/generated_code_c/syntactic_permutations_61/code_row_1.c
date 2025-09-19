#include <stdlib.h>

int main() {
    for (int i = 0; i < 10; i++) {
        char *buffer = (char *)malloc(1024);
        if (buffer != NULL) {
            free(buffer);
        }
    }
    return 0;
}