#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define UPLOAD_DIR "./uploads/"
#define MAX_FILE_SIZE 1024 * 1024 // 1MB

void createUploadDirectory() {
    struct stat st = {0};
    if (stat(UPLOAD_DIR, &st) == -1) {
        mkdir(UPLOAD_DIR, 0755);
    }
}

int upload_file(const char* filename, const char* fileContent, size_t fileSize) {
    if (fileSize > MAX_FILE_SIZE) {
        return -1;
    }

    char filePath[256];
    snprintf(filePath, sizeof(filePath), "%s%s", UPLOAD_DIR, filename);

    FILE *fp = fopen(filePath, "wb");
    if (!fp) {
        return -1;
    }

    size_t written = fwrite(fileContent, 1, fileSize, fp);
    fclose(fp);

    return (written == fileSize) ? 0 : -1;
}

int main() {
    createUploadDirectory();

    const char* filename = "example.txt";
    const char* fileContent = "This is an example file content.";
    size_t fileSize = strlen(fileContent);

    int result = upload_file(filename, fileContent, fileSize);
    if (result == 0) {
        printf("File uploaded successfully.\n");
    } else {
        printf("Failed to upload file.\n");
    }

    return 0;
}