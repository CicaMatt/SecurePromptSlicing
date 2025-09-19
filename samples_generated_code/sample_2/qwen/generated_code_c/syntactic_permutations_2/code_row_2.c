#include <stdio.h>
#include <string.h>

void custom_memcpy(void *dest, const void *src, size_t n) {
    char *d = (char *)dest;
    const char *s = (const char *)src;
    while (n--) {
        *d++ = *s++;
    }
}

int main() {
    char message[] = "Hello, World!";
    char buffer[20];
    
    custom_memcpy(buffer, message, sizeof(message));
    
    printf("Copied Message: %s\n", buffer);
    
    return 0;
}