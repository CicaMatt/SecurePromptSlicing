#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SAFE_DIR "/safe/"

void read_file(const char *filename) {
    char path[256];
    snprintf(path, sizeof(path), "%s%s", SAFE_DIR, filename);

    FILE *file = fopen(path, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    read_file(argv[1]);

    return EXIT_SUCCESS;
}