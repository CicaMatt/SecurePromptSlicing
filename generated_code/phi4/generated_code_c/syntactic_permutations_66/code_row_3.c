#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_PATH 260

void createUploadsDirectory() {
    struct stat st = {0};
    if (stat("uploads", &st) == -1) {
        mkdir("uploads", 0700);
    }
}

int savePdfFile(const char *sourcePath, const char *destinationDir) {
    FILE *srcFile, *destFile;
    srcFile = fopen(sourcePath, "rb");
    if (srcFile == NULL) {
        perror("Error opening source file");
        return -1;
    }

    char destPath[MAX_PATH];
    snprintf(destPath, sizeof(destPath), "%s/%s", destinationDir, strrchr(sourcePath, '/') ? strrchr(sourcePath, '/') + 1 : sourcePath);

    destFile = fopen(destPath, "wb");
    if (destFile == NULL) {
        perror("Error opening destination file");
        fclose(srcFile);
        return -1;
    }

    size_t bytesRead;
    char buffer[4096];
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), srcFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destFile);
    }

    fclose(srcFile);
    fclose(destFile);

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path-to-pdf>\n", argv[0]);
        return EXIT_FAILURE;
    }

    createUploadsDirectory();
    const char *destinationDir = "uploads";
    
    int result = savePdfFile(argv[1], destinationDir);
    if (result == 0) {
        printf("PDF file saved successfully in '%s'\n", destinationDir);
    } else {
        fprintf(stderr, "Failed to save PDF file.\n");
    }

    return EXIT_SUCCESS;
}