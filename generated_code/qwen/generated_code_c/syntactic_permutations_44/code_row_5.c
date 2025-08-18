#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *filename = "/safe/requestedfile.txt";
    FILE *file;
    char ch;

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
    return EXIT_SUCCESS;
}