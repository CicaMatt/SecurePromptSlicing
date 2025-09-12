#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

void send_file_to_browser(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n\r\n");
        printf("File not found");
        return;
    }
    printf("HTTP/1.1 200 OK\r\n");
    const char *content_type = strstr(file_path, ".jpg") ? "image/jpeg" : (strstr(file_path, ".png") ? "image/png" : "application/octet-stream");
    printf("Content-Type: %s\r\n\r\n", content_type);
    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }
    fclose(file);
}

void img(const char *name) {
    char path[MAX_PATH] = "images/";
    strncat(path, name, MAX_PATH - strlen(path) - 1);
    send_file_to_browser(path);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        return 1;
    }
    img(argv[1]);
    return 0;
}