#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SAFE_DIR "/safe/directory/"

void read_file(const char *filename) {
    char path[256];
    if (strlen(filename) + strlen(SAFE_DIR) >= sizeof(path)) {
        fprintf(stderr, "Filename too long\n");
        exit(1);
    }
    snprintf(path, sizeof(path), "%s%s", SAFE_DIR, filename);

    FILE *file = fopen(path, "r");
    if (!file) {
        perror("Failed to open file");
        exit(1);
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(1);
    }
    read_file(argv[1]);
    return 0;
}