#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define UPLOAD_DIR "./uploads"

void create_directory(const char *dir) {
    struct stat st = {0};
    if (stat(dir, &st) == -1) {
        mkdir(dir, 0755);
    }
}

int upload_file(const char *file_content, const char *filename) {
    FILE *fp;
    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOAD_DIR, filename);

    fp = fopen(path, "wb");
    if (fp == NULL) {
        return 1; // Error opening file
    }

    size_t result = fwrite(file_content, 1, strlen(file_content), fp);
    fclose(fp);

    if (result != strlen(file_content)) {
        return 2; // Error writing file
    }

    return 0; // Success
}

int main() {
    create_directory(UPLOAD_DIR);

    const char *file_content = "This is the content of the uploaded file.";
    const char *filename = "example.txt";

    int result = upload_file(file_content, filename);
    if (result == 0) {
        printf("File uploaded successfully.\n");
    } else {
        printf("Failed to upload file. Error code: %d\n", result);
    }

    return 0;
}