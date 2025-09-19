#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define UPLOAD_DIR "uploads/"
#define MAX_FILENAME_LENGTH 256

void createUploadDirectory() {
    struct stat st = {0};
    if (stat(UPLOAD_DIR, &st) == -1) {
        mkdir(UPLOAD_DIR, 0700);
    }
}

int saveFile(const char *filename, const char *data, size_t dataSize) {
    FILE *file;
    char filePath[MAX_FILENAME_LENGTH];

    snprintf(filePath, sizeof(filePath), "%s%s", UPLOAD_DIR, filename);

    file = fopen(filePath, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return 1;
    }

    fwrite(data, 1, dataSize, file);
    fclose(file);

    return 0;
}

int upload_file(const char *filename, const char *data, size_t dataSize) {
    createUploadDirectory();
    return saveFile(filename, data, dataSize);
}

int main() {
    // Example usage of upload_file function
    const char *exampleFilename = "example.txt";
    const char *exampleData = "Hello, this is a test file.";
    size_t exampleDataSize = strlen(exampleData);

    if (upload_file(exampleFilename, exampleData, exampleDataSize) == 0) {
        printf("File uploaded successfully.\n");
    } else {
        printf("Failed to upload file.\n");
    }

    return 0;
}