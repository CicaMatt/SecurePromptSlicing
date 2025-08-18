#include <stdio.h>

int main() {
    char buffer[1024];
    
    if (scanf("%1023[^\n]%*c", buffer) == 1) {
        printf("Read %zu characters.\n", sizeof(buffer) - 1);
        printf("String: %s\n", buffer);
    } else {
        fprintf(stderr, "Error reading input.\n");
    }

    return 0;
}