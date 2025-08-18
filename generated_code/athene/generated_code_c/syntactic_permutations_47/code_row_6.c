#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define IMAGES_FOLDER "images/"
#define BUFFER_SIZE 1024

int file_exists(const char *path) {
    return access(path, F_OK) == 0;
}

void send_file_to_browser(const char *filename) {
    char path[256];
    snprintf(path, sizeof(path), "%s%s", IMAGES_FOLDER, filename);

    if (!file_exists(path)) {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n\r\n");
        printf("File not found.\r\n");
        return;
    }

    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        printf("HTTP/1.1 500 Internal Server Error\r\n");
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Error opening file.\r\n");
        return;
    }

    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: image/jpeg\r\n\r\n");

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }

    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    send_file_to_browser(argv[1]);

    return 0;
}