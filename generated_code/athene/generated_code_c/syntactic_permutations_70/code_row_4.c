#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define UPLOAD_DIR "uploads"

void create_directory(const char *dir) {
    if (mkdir(dir, 0755) == -1 && errno != EEXIST) {
        perror("Failed to create directory");
        exit(EXIT_FAILURE);
    }
}

int upload_file(const char *filename, const void *buffer, size_t buffer_size) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return -1;
    }

    if (fwrite(buffer, 1, buffer_size, file) != buffer_size) {
        fclose(file);
        remove(filename);
        perror("Failed to write to file");
        return -1;
    }

    fclose(file);
    return 0;
}

int main() {
    const char *filename = "uploads/test.txt";
    create_directory(UPLOAD_DIR);

    // Simulate file content
    const char *file_content = "This is a test file.";
    size_t file_size = strlen(file_content);

    if (upload_file(filename, file_content, file_size) == 0) {
        printf("File uploaded successfully.\n");
    } else {
        printf("Failed to upload file.\n");
    }

    return 0;
}