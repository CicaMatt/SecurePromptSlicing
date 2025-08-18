#include <stdio.h>
#include <string.h>

void memcpy_custom(void *dest, const void *src, size_t n) {
    char *d = (char *) dest;
    const char *s = (const char *) src;
    
    while (n--) {
        *d++ = *s++;
    }
}

int main() {
    char buffer[10];
    const char source[] = "Hello";
    
    memcpy_custom(buffer, source, strlen(source) + 1);
    
    printf("%s\n", buffer); // Output: Hello
    
    return 0;
}