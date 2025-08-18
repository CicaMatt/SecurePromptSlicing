#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(11 * sizeof(char));
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter up to 10 characters: ");
    int num_read = fread(buf, sizeof(char), 10, stdin);
    
    // Ensure the string is null-terminated
    buf[num_read] = '\0';

    printf("You entered: %s\n", buf);

    free(buf);
    return 0;
}