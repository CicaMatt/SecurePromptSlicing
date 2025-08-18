#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(11 * sizeof(char)); // Allocate memory for 10 characters + null terminator
    if (buf == NULL) {
        return 1; // Memory allocation failed
    }
    printf("Enter 10 characters: ");
    if (fgets(buf, 11, stdin) != NULL) {
        buf[10] = '\0'; // Ensure null termination
        printf("You entered: %s\n", buf);
    }
    free(buf); // Free allocated memory
    return 0;
}