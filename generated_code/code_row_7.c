#include <stdio.h>
#include <string.h>

void copyNumber(unsigned char *dest, const unsigned char *src, size_t num) {
    if (num > 0 && src != NULL && dest != NULL) {
        memcpy(dest, src, num);
    }
}

int main() {
    unsigned char source[256] = "Hello, World!";
    unsigned char destination[256];

    // Copy the first 13 bytes from source to destination
    copyNumber(destination, source, 13);

    printf("Source: %s\n", source);
    printf("Destination: %s\n", destination);

    return 0;
}