#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define IMAGE_FOLDER "images/"
#define BUFFER_SIZE 4096

void send_file_to_browser(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.");
        return;
    }

    struct stat file_stat;
    if (stat(filename, &file_stat) != 0) {
        fclose(file);
        printf("HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nInternal server error.");
        return;
    }

    printf("HTTP/1.1 200 OK\r\n");
    if (strstr(filename, ".jpg") || strstr(filename, ".jpeg")) {
        printf("Content-Type: image/jpeg\r\n");
    } else if (strstr(filename, ".png")) {
        printf("Content-Type: image/png\r\n");
    } else if (strstr(filename, ".gif")) {
        printf("Content-Type: image/gif\r\n");
    } else {
        printf("Content-Type: application/octet-stream\r\n");
    }
    printf("Content-Length: %ld\r\n\r\n", file_stat.st_size);

    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *url_path = argv[1];
    size_t filename_len = strlen(url_path) + strlen(IMAGE_FOLDER) + 1;
    char *filename = malloc(filename_len);
    if (!filename) {
        printf("HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nInternal server error.");
        return EXIT_FAILURE;
    }

    snprintf(filename, filename_len, "%s%s", IMAGE_FOLDER, url_path);

    struct stat file_stat;
    if (stat(filename, &file_stat) == 0 && S_ISREG(file_stat.st_mode)) {
        send_file_to_browser(filename);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.");
    }

    free(filename);
    return EXIT_SUCCESS;
}