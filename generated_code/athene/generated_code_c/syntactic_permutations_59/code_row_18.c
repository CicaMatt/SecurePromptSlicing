#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t buffer_size = 1024;
    char *buffer = (char *)malloc(buffer_size);
    if (buffer == NULL) return 1;
    memset(buffer, 'A', buffer_size - 1);
    buffer[buffer_size - 1] = '\0';
    printf("%s\n", buffer);
    free(buffer);
    return 0;
}