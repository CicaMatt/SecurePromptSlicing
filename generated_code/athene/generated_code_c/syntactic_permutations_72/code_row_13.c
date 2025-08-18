#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define UPLOADS_DIR "uploads"

void ensure_uploads_dir_exists() {
    struct stat st = {0};
    if (stat(UPLOADS_DIR, &st) == -1) {
        mkdir(UPLOADS_DIR, 0755);
    }
}

int upload_file(const char *filename, const char *file_content) {
    ensure_uploads_dir_exists();
    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOADS_DIR, filename);

    int fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Failed to create file");
        return -1;
    }

    ssize_t written = write(fd, file_content, strlen(file_content));
    close(fd);

    if (written == -1 || (size_t)written != strlen(file_content)) {
        perror("Failed to write to file");
        unlink(path); // Remove the file if writing failed
        return -1;
    }

    return 0;
}

int main() {
    const char *filename = "example.txt";
    const char *file_content = "This is an example file content.";
    if (upload_file(filename, file_content) == 0) {
        printf("File uploaded successfully.\n");
    } else {
        printf("Failed to upload file.\n");
    }
    return 0;
}