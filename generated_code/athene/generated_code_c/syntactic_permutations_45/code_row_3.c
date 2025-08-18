#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SAFE_DIR "/safe_directory/"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    char path[256];
    snprintf(path, sizeof(path), "%s%s", SAFE_DIR, argv[1]);

    FILE *file = fopen(path, "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
    return 0;
}