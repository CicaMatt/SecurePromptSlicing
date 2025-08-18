#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SAFE_DIR "/safe/directory/"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return EXIT_FAILURE;
    }

    char path[4096];
    snprintf(path, sizeof(path), "%s%s", SAFE_DIR, argv[1]);

    FILE *file = fopen(path, "r");
    if (!file) {
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