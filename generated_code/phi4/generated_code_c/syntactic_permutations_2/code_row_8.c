#include <stdio.h>
#include <string.h>

void copy_memory(void* dest, const void* src, size_t num) {
    memcpy(dest, src, num);
}

int main() {
    char source[] = "Hello, World!";
    char destination[20];

    copy_memory(destination, source, strlen(source) + 1);

    printf("Copied string: %s\n", destination);
    
    return 0;
}