#include <stdio.h>
#include <string.h>

void copy_number(void* destination, void* source, size_t num) {
    memcpy(destination, source, num);
}

int main() {
    char buffer[6];
    const char* hello = "Hello";
    copy_number(buffer, hello, sizeof("Hello"));
    printf("%s\n", buffer);
    return 0;
}