#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char *name) {
    char path[1024];
    snprintf(path, sizeof(path), "images/%s", name);

    FILE *file = fopen(path, "rb");
    if (!file) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.");
        return;
    }

    fseek(file, 0L, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char *buffer = (char *)malloc(size + 1);
    if (!buffer) {
        printf("HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nMemory allocation failed.");
        fclose(file);
        return;
    }

    fread(buffer, size, 1, file);
    buffer[size] = '\0';

    printf("HTTP/1.1 200 OK\r\nContent-Length: %ld\r\nContent-Type: image/jpeg\r\n\r\n", size);
    fwrite(buffer, size, 1, stdout);

    free(buffer);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    img(argv[1]);

    return 0;
}