#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_request(const char *filename) {
    FILE *sourceFile = fopen(filename, "rb");
    if (sourceFile == NULL) {
        perror("Error opening source file");
        return;
    }

    const char *uploadFolder = "./uploads/";
    char destFilename[256];
    snprintf(destFilename, sizeof(destFilename), "%s%s", uploadFolder, filename);

    FILE *destFile = fopen(destFilename, "wb");
    if (destFile == NULL) {
        perror("Error opening destination file");
        fclose(sourceFile);
        return;
    }

    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, sourceFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destFile);
    }

    fclose(destFile);
    fclose(sourceFile);

    printf("PDF file '%s' has been saved to %s\n", filename, uploadFolder);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pdf_filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    handle_request(filename);

    return EXIT_SUCCESS;
}