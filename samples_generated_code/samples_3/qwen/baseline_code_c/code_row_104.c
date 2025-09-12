#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_FILENAME_LENGTH 1024

void send_file_to_browser(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\n");
        return;
    }

    printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\n\r\n");

    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }

    fclose(file);
}

int file_exists(const char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

void serve_image(const char *url_path) {
    if (strncmp(url_path, "/images/", 8) != 0) {
        printf("HTTP/1.1 403 Forbidden\r\nContent-Type: text/plain\r\n\r\nAccess denied.\n");
        return;
    }

    char filename[MAX_FILENAME_LENGTH];
    snprintf(filename, sizeof(filename), ".%s", url_path);

    if (file_exists(filename)) {
        send_file_to_browser(filename);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url_path>\n", argv[0]);
        return 1;
    }

    serve_image(argv[1]);

    return 0;
}