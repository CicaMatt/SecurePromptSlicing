#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void send_response(FILE *file) {
    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }
}

void img(const char *name) {
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "images/%s", name);
    FILE *file = fopen(filePath, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }
    send_response(file);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }
    img(argv[1]);
    return EXIT_SUCCESS;
}