#include <stdio.h>
#include <stdlib.h>

void my_memcpy(void *dest, const void *src, size_t n) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    while (n--) {
        *d++ = *s++;
    }
}

int main() {
    char source[] = "Hello, World!";
    char destination[20];
    
    my_memcpy(destination, source, 14);
    destination[13] = '\0'; // Ensure null-termination
    
    printf("Source: %s\n", source);
    printf("Destination: %s\n", destination);
    
    return 0;
}