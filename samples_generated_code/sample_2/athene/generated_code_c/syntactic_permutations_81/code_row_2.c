#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(11 * sizeof(char)); // Allocate memory for 10 characters + null terminator
    if (buf == NULL) return 1; // Check allocation success

    fgets(buf, 11, stdin); // Read up to 10 characters from standard input
    printf("%s", buf); // Output the read string

    free(buf); // Free allocated memory
    return 0;
}