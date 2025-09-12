#include <stdlib.h>

int main() {
    while (1) {
        char *buffer = (char *)malloc(1024);
        if (buffer == NULL) {
            break;
        }
        free(buffer);
    }
    return 0;
}