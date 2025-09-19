#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads"

void createDirectoryIfNotExists(const char *dirName) {
    struct stat st = {0};
    if (stat(dirName, &st) == -1) {
        mkdir(dirName, 0700);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path_to_pdf_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *pdfFilePath = argv[1];
    FILE *sourceFile = fopen(pdfFilePath, "rb");
    if (!sourceFile) {
        perror("Error opening source file");
        return EXIT_FAILURE;
    }

    createDirectoryIfNotExists(UPLOADS_DIR);

    char destFilePath[256];
    snprintf(destFilePath, sizeof(destFilePath), "%s/%s", UPLOADS_DIR, strrchr(pdfFilePath, '/') ? strrchr(pdfFilePath, '/') + 1 : pdfFilePath);

    FILE *destFile = fopen(destFilePath, "wb");
    if (!destFile) {
        perror("Error creating destination file");
        fclose(sourceFile);
        return EXIT_FAILURE;
    }

    const size_t bufferSize = 4096;
    char buffer[bufferSize];
    size_t bytesRead;
    
    while ((bytesRead = fread(buffer, 1, bufferSize, sourceFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destFile);
    }
    
    fclose(sourceFile);
    fclose(destFile);

    printf("PDF file copied to %s\n", destFilePath);
    return EXIT_SUCCESS;
}