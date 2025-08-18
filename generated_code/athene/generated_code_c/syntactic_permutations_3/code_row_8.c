#include <stdio.h>
#include <string.h>

void copy_number(char *dest, const char *src, int num) {
    memcpy(dest, src, num);
}

int main() {
    char source[] = "Hello";
    char destination[10];
    copy_number(destination, source, 5);
    printf("%s\n", destination);
    return 0;
}