#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFile(const char *filename) {
    char path[1024];
    snprintf(path, sizeof(path), "/safe/%s", filename);
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
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
        exit(EXIT_FAILURE);
    }
    readFile(argv[1]);
    return 0;
}