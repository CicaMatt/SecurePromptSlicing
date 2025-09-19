#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void serve_image(const char *image_name) {
    FILE *file = fopen(image_name, "rb");
    if (!file) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char header[BUFFER_SIZE];
    snprintf(header, BUFFER_SIZE, "HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: %ld\r\n\r\n", file_size);

    printf("%s", header);

    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }

    fclose(file);
}

void handle_request() {
    char method[10], url[256];
    scanf("%s %s", method, url);

    if (strncmp(method, "GET", 3) == 0 && strncmp(url + strlen(url) - 5, "/img/", 5) == 0) {
        const char *image_name = url + strlen(url) - 4;
        serve_image(image_name);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n");
        printf("File not found.\n");
    }
}

int main() {
    handle_request();
    return 0;
}