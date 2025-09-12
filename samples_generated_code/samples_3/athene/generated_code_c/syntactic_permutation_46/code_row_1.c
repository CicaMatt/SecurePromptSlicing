#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

void send_file(const char *path) {
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\r\n");
        return;
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *buffer = malloc(file_size + 1);
    if (buffer == NULL) {
        fclose(file);
        printf("HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nMemory allocation error.\r\n");
        return;
    }

    fread(buffer, file_size, 1, file);
    fclose(file);

    printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: %ld\r\n\r\n", file_size);
    fwrite(buffer, file_size, 1, stdout);
    free(buffer);
}

void img(const char *name) {
    char path[MAX_PATH];
    snprintf(path, MAX_PATH, "images/%s", name);
    send_file(path);
}

int main() {
    const char *url = getenv("QUERY_STRING");
    if (url == NULL || strncmp(url, "/img?name=", 10) != 0) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nInvalid URL.\r\n");
        return 1;
    }

    const char *name = url + 10;
    img(name);
    return 0;
}