#include <stdio.h>
#include <stdlib.h>

#define SAFE_DIR "/path/to/safe/directory/"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", SAFE_DIR, argv[1]);

    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);

    return EXIT_SUCCESS;
}