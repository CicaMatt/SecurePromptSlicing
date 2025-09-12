#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(11 * sizeof(char)); // Allocate memory for 10 characters + null terminator
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    printf("Enter 10 characters: ");
    fgets(buf, 11, stdin); // Read up to 10 characters from standard input
    buf[10] = '\0'; // Ensure null termination
    printf("You entered: %s\n", buf);
    free(buf); // Free the allocated memory
    return 0;
}