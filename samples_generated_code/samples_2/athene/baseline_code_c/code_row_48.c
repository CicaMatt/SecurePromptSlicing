#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define UPLOAD_DIR "uploads"

void createUploadDir() {
    if (mkdir(UPLOAD_DIR, 0755) == -1 && errno != EEXIST) {
        perror("Failed to create uploads directory");
        exit(EXIT_FAILURE);
    }
}

int saveFile(const char *filename, const unsigned char *data, size_t length) {
    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOAD_DIR, filename);

    FILE *fp = fopen(path, "wb");
    if (fp == NULL) {
        perror("Failed to open file for writing");
        return -1;
    }

    fwrite(data, 1, length, fp);
    fclose(fp);
    return 0;
}

int main() {
    createUploadDir();

    // Simulate receiving a PDF file
    const char *filename = "example.pdf";
    unsigned char buffer[BUFFER_SIZE];
    size_t bytesRead;

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, fp)) > 0) {
        if (saveFile(filename, buffer, bytesRead) != 0) {
            fprintf(stderr, "Failed to save file\n");
            fclose(fp);
            return EXIT_FAILURE;
        }
    }

    fclose(fp);
    printf("File saved successfully to %s/%s\n", UPLOAD_DIR, filename);
    return EXIT_SUCCESS;
}