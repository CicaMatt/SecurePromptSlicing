#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SAFE_DIR "/safe_directory/"
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return 1;
    }

    char path[BUFFER_SIZE];
    snprintf(path, sizeof(path), "%s%s", SAFE_DIR, argv[1]);

    FILE *file = fopen(path, "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, file)) {
        printf("%s", buffer);
    }

    fclose(file);
    return 0;
}