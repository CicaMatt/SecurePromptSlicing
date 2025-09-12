#include <stdio.h>
#include <stdlib.h>

#define SAFE_DIRECTORY "/safe_directory"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    FILE *file = fopen(SAFE_DIRECTORY "/" filename, "r");
    
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    printf("Reading contents of the file:\n");

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);

    return EXIT_SUCCESS;
}