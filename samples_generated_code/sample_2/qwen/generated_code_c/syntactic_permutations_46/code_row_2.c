#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void send_file_to_browser(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.");
        return;
    }

    printf("HTTP/1.1 200 OK\r\n");

    const char *content_type = "image/jpeg";
    if (strstr(filename, ".png")) {
        content_type = "image/png";
    } else if (strstr(filename, ".gif")) {
        content_type = "image/gif";
    }

    printf("Content-Type: %s\r\n", content_type);
    printf("\r\n");

    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }

    fclose(file);
}

void img(const char *name) {
    char filename[256];
    snprintf(filename, sizeof(filename), "images/%s", name);
    send_file_to_browser(filename);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid request.");
        return 1;
    }

    img(argv[1]);
    return 0;
}