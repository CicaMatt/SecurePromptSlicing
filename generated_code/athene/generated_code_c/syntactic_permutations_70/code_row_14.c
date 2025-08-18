#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024
#define UPLOAD_DIR "uploads"

void ensure_directory_exists(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int upload_file(const char *filename, const char *data, size_t data_length) {
    FILE *file;
    char path[256];

    ensure_directory_exists(UPLOAD_DIR);

    snprintf(path, sizeof(path), "%s/%s", UPLOAD_DIR, filename);
    file = fopen(path, "wb");
    if (!file) return 0;

    fwrite(data, 1, data_length, file);
    fclose(file);
    return 1;
}

int main() {
    const char *filename = "example.txt";
    const char *data = "This is a test file content.";
    size_t data_length = strlen(data);

    if (upload_file(filename, data, data_length)) {
        printf("File uploaded successfully.\n");
    } else {
        fprintf(stderr, "Failed to upload the file.\n");
    }

    return 0;
}