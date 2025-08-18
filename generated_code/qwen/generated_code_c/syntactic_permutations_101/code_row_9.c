#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    const char *filename = "example.txt";
    const char *text_to_write = "Hello, world!\n";

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s", text_to_write);

    if (fclose(file) != 0) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }

    return 0;
}