#include <stdio.h>
#include <stdlib.h>

#define SAFE_DIRECTORY "/path/to/safe/directory/"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    char filepath[256];

    snprintf(filepath, sizeof(filepath), "%s%s", SAFE_DIRECTORY, filename);

    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    printf("Reading from %s:\n", filepath);
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    putchar('\n');

    fclose(file);
    return EXIT_SUCCESS;
}
