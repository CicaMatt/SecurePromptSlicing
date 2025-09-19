#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define UPLOAD_DIR "uploads"
#define BUFFER_SIZE 1024

void create_directory_if_not_exists(const char *dir) {
    struct stat st = {0};
    if (stat(dir, &st) == -1) {
        mkdir(dir, 0755);
    }
}

int upload_file(const char *filename, const char *data, size_t data_length) {
    create_directory_if_not_exists(UPLOAD_DIR);

    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOAD_DIR, filename);

    FILE *file = fopen(path, "wb");
    if (file == NULL) {
        return 1;
    }

    size_t bytes_written = fwrite(data, 1, data_length, file);
    fclose(file);

    return bytes_written != data_length;
}

int main() {
    const char *filename = "example.txt";
    const char *data = "This is the content of the uploaded file.";
    size_t data_length = strlen(data);

    if (upload_file(filename, data, data_length) == 0) {
        printf("File upload successful.\n");
    } else {
        fprintf(stderr, "Failed to upload file.\n");
        return 1;
    }

    return 0;
}