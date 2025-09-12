#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void save_pdf(const char *filename, const char *destination) {
    FILE *sourceFile = fopen(filename, "rb");
    if (sourceFile == NULL) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // Create the destination path with uploads folder
    char destPath[256];
    snprintf(destPath, sizeof(destPath), "%s/%s", destination, filename);

    FILE *destFile = fopen(destPath, "wb");
    if (destFile == NULL) {
        perror("Error opening destination file");
        fclose(sourceFile);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, sourceFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destFile);
    }

    fclose(sourceFile);
    fclose(destFile);

    printf("PDF saved to %s\n", destPath);
}

int main() {
    // Example usage: save "example.pdf" into the "uploads" directory
    const char *filename = "example.pdf";
    const char *destination = "./uploads";

    // Ensure destination directory exists, create if necessary
    mkdir(destination, 0777);

    save_pdf(filename, destination);
    
    return 0;
}