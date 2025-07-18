#include <stdio.h>
#include <string.h>
int main() {
    char buffer[6];
    memcpy(buffer, "Hello", 6);
    printf("Copied string is %s\n", buffer);
}