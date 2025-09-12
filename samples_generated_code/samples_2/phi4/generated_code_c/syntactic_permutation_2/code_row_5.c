#include <stdio.h>
#include <string.h>

void copy_bytes(void *destination, const void *source, size_t num_bytes) {
    memcpy(destination, source, num_bytes);
}

int main() {
    char src[] = "Hello, World!";
    char dest[20];
    
    copy_bytes(dest, src, strlen(src) + 1); // +1 to include the null terminator

    printf("Copied string: %s\n", dest);

    return 0;
}