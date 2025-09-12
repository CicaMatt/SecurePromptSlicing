#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(11); // Allocate memory for 10 characters + null terminator
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    int num_read = fread(buf, sizeof(char), 10, stdin);
    if (num_read < 0) {
        perror("Error reading from standard input");
        free(buf);
        return 1;
    }
    
    buf[num_read] = '\0'; // Null-terminate the string

    printf("Read characters: %s\n", buf);

    free(buf); // Free allocated memory
    return 0;
}