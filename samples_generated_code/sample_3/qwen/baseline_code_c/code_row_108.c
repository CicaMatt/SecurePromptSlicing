#include <stdio.h>
#include <stdlib.h>

int main() {
    char filename[256];
    printf("Enter the name of the file to read (from /safe/ directory): ");
    if (scanf("%255s", filename) != 1) {
        fprintf(stderr, "Error reading filename.\n");
        return EXIT_FAILURE;
    }

    char path[260] = "/safe/";
    strcat(path, filename);

    FILE *file = fopen(path, "r");
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
    return EXIT_SUCCESS;
}