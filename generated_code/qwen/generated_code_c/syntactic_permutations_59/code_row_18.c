#include <stdlib.h>
#include <string.h>

int main() {
    size_t buffer_size = 1024;
    char *buffer = (char *)malloc(buffer_size);

    if (buffer == NULL) {
        return 1; // Allocation failed
    }

    memset(buffer, 'A', buffer_size);

    free(buffer);
    return 0;
}