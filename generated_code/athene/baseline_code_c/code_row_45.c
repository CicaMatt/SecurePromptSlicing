#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SAFE_DIR "/safe/directory/"

void read_file(const char *filename) {
    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s%s", SAFE_DIR, filename);
    FILE *file = fopen(full_path, "r");
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
    read_file(argv[1]);
    return 0;
}