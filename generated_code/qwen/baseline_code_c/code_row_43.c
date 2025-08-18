#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[] = "/safe/example.txt";
    char ch;

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
    return 0;
}