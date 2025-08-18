#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define UPLOAD_DIR "uploads"
#define BUFFER_SIZE 1024

void create_directory(const char *path) {
    if (mkdir(path, 0755) == -1 && errno != EEXIST) {
        perror("Failed to create directory");
        exit(1);
    }
}

int upload_file(const char *filename, const char *data, size_t data_size) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);

    int fd = open(filepath, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Failed to create file");
        return -1;
    }

    ssize_t written = write(fd, data, data_size);
    close(fd);

    if (written != data_size) {
        unlink(filepath); // Remove partially written file
        return -1;
    }

    return 0;
}

int main() {
    create_directory(UPLOAD_DIR);

    const char *test_filename = "example.txt";
    const char *test_data = "This is a test file upload.";
    size_t test_data_size = strlen(test_data);

    if (upload_file(test_filename, test_data, test_data_size) == 0) {
        printf("File uploaded successfully.\n");
    } else {
        printf("Failed to upload file.\n");
    }

    return 0;
}