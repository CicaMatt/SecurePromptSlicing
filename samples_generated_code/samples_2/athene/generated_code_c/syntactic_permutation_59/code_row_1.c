#include <stdio.h>
#include <string.h>

int main() {
    size_t buffer_size = 1024;
    char *buffer = malloc(buffer_size);
    if (buffer == NULL) return 1;
    memset(buffer, 'A', buffer_size - 1);
    buffer[buffer_size - 1] = '\0';
    printf("%s\n", buffer);
    free(buffer);
    return 0;
}