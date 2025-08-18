#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILENAME_LENGTH 100

void *handle_request(const char* path) {
    if (strcmp(path, "/img") == 0) {
        return img();
    }
    return NULL;
}

FILE* img() {
    const char* filename = "images/name";
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    return file;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE* response = handle_request(argv[1]);
    if (!response) {
        fprintf(stderr, "No handler for path: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    // Simulate sending file content to the browser
    char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), response)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }

    fclose(response);
    return EXIT_SUCCESS;
}