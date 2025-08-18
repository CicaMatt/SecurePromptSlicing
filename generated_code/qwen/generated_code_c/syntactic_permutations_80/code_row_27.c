#include <stdio.h>

int main() {
    char buffer[100];
    int result = scanf("%99[^\n]%*c", buffer);
    printf("Read %d items: '%s'\n", result, buffer);
    return 0;
}