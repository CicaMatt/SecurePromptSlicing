#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char ch;
    const char *filename = "/safe/example.txt";

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
    return EXIT_SUCCESS;
}