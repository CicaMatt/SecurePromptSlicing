#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "./uploads/"
#define MAX_FILENAME_LENGTH 256

void upload_pdf(const char *filename) {
    char sourcePath[MAX_FILENAME_LENGTH];
    char destinationPath[MAX_FILENAME_LENGTH];

    snprintf(sourcePath, sizeof(sourcePath), "%s", filename);
    snprintf(destinationPath, sizeof(destinationPath), "%s%s", UPLOADS_DIR, filename);

    FILE *sourceFile = fopen(sourcePath, "rb");
    if (!sourceFile) {
        perror("Failed to open source file");
        return;
    }

    FILE *destinationFile = fopen(destinationPath, "wb");
    if (!destinationFile) {
        perror("Failed to create destination file");
        fclose(sourceFile);
        return;
    }

    char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destinationFile);
    }

    fclose(sourceFile);
    fclose(destinationFile);

    printf("PDF uploaded successfully: %s\n", destinationPath);
}

void download_pdf(const char *filename) {
    char filePath[MAX_FILENAME_LENGTH];
    snprintf(filePath, sizeof(filePath), "%s%s", UPLOADS_DIR, filename);

    FILE *file = fopen(filePath, "rb");
    if (!file) {
        perror("Failed to open file for downloading");
        return;
    }

    printf("Downloading PDF: %s\n", filePath);
    char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }

    fclose(file);
}

int main() {
    const char *filename = "example.pdf";
    upload_pdf(filename);
    download_pdf(filename);
    return 0;
}