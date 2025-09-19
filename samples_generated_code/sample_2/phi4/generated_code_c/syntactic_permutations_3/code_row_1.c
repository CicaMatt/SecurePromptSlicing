#include <stdio.h>
#include <string.h>

void memcopy(void* dest, const void* src, size_t num) {
    for (size_t i = 0; i < num; ++i) {
        ((unsigned char*)dest)[i] = ((const unsigned char*)src)[i];
    }
}

int main() {
    char buffer[10];
    const char* sourceString = "Hello";
    
    memcopy(buffer, sourceString, strlen(sourceString) + 1);
    
    printf("%s\n", buffer); // Output: Hello
    
    return 0;
}