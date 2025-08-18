#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define UPLOAD_DIR "uploads"
#define BUFFER_SIZE 1024

void save_file(const char *filename, const char *data, size_t length) {
    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOAD_DIR, filename);
    
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    ssize_t written = write(fd, data, length);
    if (written != (ssize_t)length) {
        perror("Error writing to file");
        close(fd);
        unlink(path); // Remove partially written file
        exit(EXIT_FAILURE);
    }

    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <filename> <data>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    const char *data = argv[2];
    size_t length = strlen(data);

    // Ensure upload directory exists
    if (mkdir(UPLOAD_DIR, 0755) == -1 && errno != EEXIST) {
        perror("Error creating uploads directory");
        return EXIT_FAILURE;
    }

    save_file(filename, data, length);
    printf("File saved successfully.\n");

    return EXIT_SUCCESS;
}