#include <stdio.h>

int main() {
    char buffer[1024];
    int result = scanf("%1023[^\n]%*c", buffer);
    printf("Read %d item(s): '%s'\n", result, buffer);
    return 0;
}