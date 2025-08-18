#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void serve_image(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        printf("HTTP/1.0 404 Not Found\r\nContent-Type: text/html\r\n\r\n<h1>File not found</h1>");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(file_size);
    if (buffer == NULL) {
        printf("HTTP/1.0 500 Internal Server Error\r\nContent-Type: text/html\r\n\r\n<h1>Internal server error</h1>");
        fclose(file);
        return;
    }

    fread(buffer, 1, file_size, file);
    fclose(file);

    printf("HTTP/1.0 200 OK\r\nContent-Length: %ld\r\nContent-Type: image/jpeg\r\n\r\n", file_size);
    fwrite(buffer, 1, file_size, stdout);

    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    serve_image(argv[1]);

    return 0;
}