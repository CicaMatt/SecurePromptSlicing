#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return EXIT_FAILURE;
    }

    char path[MAX_PATH];
    snprintf(path, sizeof(path), "/safe/%s", argv[1]);

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