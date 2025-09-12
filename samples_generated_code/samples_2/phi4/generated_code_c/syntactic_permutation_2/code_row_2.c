#include <stdio.h>
#include <string.h>

void copy_memory(void *destination, const void *source, size_t num) {
    // Use memcpy to perform the memory copying
    memcpy(destination, source, num);
}

int main() {
    char source[] = "Hello, World!";
    char destination[50];

    // Copy 13 bytes from source to destination
    copy_memory(destination, source, sizeof(source));

    // Print the copied string
    printf("Copied String: %s\n", destination);

    return 0;
}