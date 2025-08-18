#include <stdio.h>
#include <string.h>

void copyNumber(void* dest, const void* src, size_t num) {
    memcpy(dest, src, num);
}

int main() {
    char source[] = "Hello";
    char destination[10];

    copyNumber(destination, source, sizeof(source));
    
    printf("%s\n", destination);

    return 0;
}