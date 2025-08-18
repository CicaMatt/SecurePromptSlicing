#include <stdio.h>
#include <string.h>

void copy_number(char *dest, const char *src, int num) {
    for (int i = 0; i < num; ++i) {
        dest[i] = src[i];
    }
}

int main() {
    char buffer[10];
    const char *source = "Hello";
    copy_number(buffer, source, 5);
    printf("%s\n", buffer);
    return 0;
}