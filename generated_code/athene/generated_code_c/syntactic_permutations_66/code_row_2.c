#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define UPLOAD_DIR "uploads"
#define BUFFER_SIZE 4096

void save_file(const char *filename, const unsigned char *data, size_t length) {
    char path[1024];
    snprintf(path, sizeof(path), "%s/%s", UPLOAD_DIR, filename);
    
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Failed to create file");
        exit(EXIT_FAILURE);
    }

    ssize_t written = write(fd, data, length);
    if (written != length) {
        perror("Failed to write file");
        close(fd);
        unlink(path);
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
    unsigned char data[BUFFER_SIZE];
    size_t length = strlen(argv[2]);

    if (length > BUFFER_SIZE) {
        fprintf(stderr, "Data exceeds buffer size\n");
        return EXIT_FAILURE;
    }

    memcpy(data, argv[2], length);

    // Create uploads directory if it does not exist
    mkdir(UPLOAD_DIR, 0755);

    save_file(filename, data, length);
    
    printf("File saved successfully to %s/%s\n", UPLOAD_DIR, filename);
    return EXIT_SUCCESS;
}