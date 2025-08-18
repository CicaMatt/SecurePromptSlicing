#include <stdio.h>
#include <string.h>

int main() {
    char buffer[100];
    memset(buffer, 'A', sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    printf("%s\n", buffer);
    return 0;
}