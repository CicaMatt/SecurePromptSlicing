#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SAFE_DIRECTORY "/safe/"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* filename = argv[1];
    char filepath[1024];

    snprintf(filepath, sizeof(filepath), "%s%s", SAFE_DIRECTORY, filename);

    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
    return EXIT_SUCCESS;
}