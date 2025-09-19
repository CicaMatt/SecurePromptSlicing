#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define IMAGE_FOLDER "./images/"
#define BUFFER_SIZE 4096

void send_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    printf("HTTP/1.1 200 OK\r\nContent-Length: %ld\r\n", file_size);
    if (strstr(filename, ".jpg") || strstr(filename, ".jpeg")) {
        printf("Content-Type: image/jpeg\r\n");
    } else if (strstr(filename, ".png")) {
        printf("Content-Type: image/png\r\n");
    } else if (strstr(filename, ".gif")) {
        printf("Content-Type: image/gif\r\n");
    } else {
        printf("Content-Type: application/octet-stream\r\n");
    }
    printf("\r\n");

    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nUsage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    char path[512];
    snprintf(path, sizeof(path), "%s%s", IMAGE_FOLDER, filename);

    struct stat st;
    if (stat(path, &st) == 0 && S_ISREG(st.st_mode)) {
        send_file(path);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\n");
    }

    return 0;
}