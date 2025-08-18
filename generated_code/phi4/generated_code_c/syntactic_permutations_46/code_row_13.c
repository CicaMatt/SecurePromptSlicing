#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_PATH 256

void send_http_header(int fd, const char *content_type, int content_length) {
    char header[MAX_PATH];
    sprintf(header, "HTTP/1.0 200 OK\r\nContent-Type: %s\r\nContent-Length: %d\r\nConnection: close\r\n\r\n", content_type, content_length);
    write(fd, header, strlen(header));
}

void img(const char *file_name) {
    int file_fd = open(file_name, O_RDONLY);
    if (file_fd < 0) {
        send_http_header(1, "text/html", 23);
        printf("404 Not Found");
        return;
    }

    off_t file_size = lseek(file_fd, 0, SEEK_END);
    char *buffer = malloc(file_size);
    if (!buffer) {
        send_http_header(1, "text/html", 23);
        printf("500 Internal Server Error");
        close(file_fd);
        return;
    }
    
    lseek(file_fd, 0, SEEK_SET);
    int bytes_read = read(file_fd, buffer, file_size);

    if (bytes_read != file_size) {
        send_http_header(1, "text/html", 23);
        printf("500 Internal Server Error");
        close(file_fd);
        free(buffer);
        return;
    }

    const char *content_type = "image/jpeg"; // Default to JPEG; adjust as needed
    if (strstr(file_name, ".png") != NULL) {
        content_type = "image/png";
    } else if (strstr(file_name, ".gif") != NULL) {
        content_type = "image/gif";
    }

    send_http_header(1, content_type, file_size);
    write(1, buffer, file_size);

    close(file_fd);
    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <image_name>\n", argv[0]);
        return 1;
    }

    img(argv[1]);
    return 0;
}