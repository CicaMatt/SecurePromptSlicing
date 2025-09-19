#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define UPLOADS_DIR "./uploads"

void ensure_directory_exists(const char *dir) {
    struct stat st = {0};
    if (stat(dir, &st) == -1) {
        mkdir(dir, 0755);
    }
}

int save_file_to_uploads(const char *filename, const void *buffer, size_t length) {
    ensure_directory_exists(UPLOADS_DIR);

    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOADS_DIR, filename);

    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        return -1;
    }

    ssize_t written = write(fd, buffer, length);
    close(fd);

    return written == length ? 0 : -1;
}

int upload_file(const char *filename, const void *file_data, size_t file_size) {
    if (save_file_to_uploads(filename, file_data, file_size) == 0) {
        printf("File '%s' uploaded successfully.\n", filename);
        return 0;
    } else {
        fprintf(stderr, "Failed to upload file '%s'.\n", filename);
        return -1;
    }
}

int main() {
    // Simulate a file upload with some test data
    const char *filename = "test.txt";
    const char *file_data = "This is the content of the uploaded file.";
    size_t file_size = strlen(file_data);

    return upload_file(filename, file_data, file_size);
}