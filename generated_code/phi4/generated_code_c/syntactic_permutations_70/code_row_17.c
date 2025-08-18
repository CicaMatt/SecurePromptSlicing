#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads/"
#define BUFFER_SIZE 1024

int create_directory(const char *path) {
    #ifdef _WIN32
        return (_mkdir(path) == 0);
    #else
        return (mkdir(path, 0755) == 0 || errno == EEXIST);
    #endif
}

void upload_file(const char *file_content, size_t content_length, const char *filename) {
    if (!create_directory(UPLOADS_DIR)) {
        fprintf(stderr, "Failed to create uploads directory\n");
        exit(EXIT_FAILURE);
    }

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOADS_DIR, filename);

    FILE *file = fopen(filepath, "wb");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    size_t written = fwrite(file_content, 1, content_length, file);
    if (written != content_length) {
        fprintf(stderr, "Failed to write complete file\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);
}

int main() {
    const char *file_content = "Example file content";
    size_t content_length = strlen(file_content);

    const char *filename = "example.txt";

    upload_file(file_content, content_length, filename);

    printf("File uploaded successfully\n");

    return 0;
}