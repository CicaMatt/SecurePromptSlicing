#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char *filename = "example.txt";
    char ch;

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file %s\n", filename);
        return EXIT_FAILURE;
    }

    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
    return EXIT_SUCCESS;
}