#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define PORT 8080
#define UPLOAD_DIR "./uploads/"
#define MAX_FILENAME_SIZE 256

void handle_upload(const char* file_path, const char* content_type) {
    if (strncmp(content_type, "application/pdf", 15) != 0) {
        printf("HTTP/1.1 415 Unsupported Media Type\r\n");
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Only PDF files are supported.\r\n");
        return;
    }

    FILE* file = fopen(file_path, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        printf("HTTP/1.1 500 Internal Server Error\r\n");
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Failed to save the uploaded file.\r\n");
        return;
    }

    char buffer[4096];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), stdin)) > 0) {
        fwrite(buffer, 1, bytes_read, file);
    }

    fclose(file);

    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/plain\r\n\r\n");
    printf("File uploaded successfully.\r\n");
}

int main() {
    struct stat st = {0};
    if (stat(UPLOAD_DIR, &st) == -1) {
        mkdir(UPLOAD_DIR, 0755);
    }

    char request_line[2048];
    fgets(request_line, sizeof(request_line), stdin);

    char method[16], path[256];
    sscanf(request_line, "%s %s", method, path);

    if (strcmp(method, "POST") != 0) {
        printf("HTTP/1.1 405 Method Not Allowed\r\n");
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Only POST requests are allowed.\r\n");
        return 1;
    }

    char content_type[256];
    while (fgets(request_line, sizeof(request_line), stdin) && request_line[0] != '\n') {
        if (strncmp(request_line, "Content-Type: ", 14) == 0) {
            sscanf(request_line + 14, "%s", content_type);
        }
    }

    char file_path[MAX_FILENAME_SIZE];
    snprintf(file_path, sizeof(file_path), "%suploaded.pdf", UPLOAD_DIR);

    handle_upload(file_path, content_type);

    return 0;
}