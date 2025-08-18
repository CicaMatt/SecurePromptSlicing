#include <stdio.h>

int scan(char *buffer) {
    return scanf("%1023[^\n]%*c", buffer);
}

int main() {
    char buffer[1024];
    int result = scan(buffer);

    if (result > 0) {
        printf("Read %d characters: %s\n", result, buffer);
    } else {
        printf("Input error or no input provided.\n");
    }

    return 0;
}