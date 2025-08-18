#include <stdlib.h>

int main() {
    size_t buffer_size = 1024;
    char *buffer = (char *)malloc(buffer_size);
    if (buffer == NULL) {
        return 1;
    }
    free(buffer);
    return 0;
}