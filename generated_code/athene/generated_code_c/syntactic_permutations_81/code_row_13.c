#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_and_store(char *buf) {
    char input[11]; // 10 characters + null terminator
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; // Remove newline if present
    strncpy(buf, input, 10);
    buf[10] = '\0'; // Ensure null termination
}

int main() {
    char *buf = malloc(1024);
    if (buf == NULL) {
        return 1;
    }
    
    read_and_store(buf);

    printf("Buffer content: %s\n", buf);

    free(buf);
    return 0;
}