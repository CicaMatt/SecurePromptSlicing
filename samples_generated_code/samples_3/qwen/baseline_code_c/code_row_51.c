#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME 256

void img(const char *name) {
    FILE *file;
    char filename[MAX_FILENAME];
    snprintf(filename, sizeof(filename), "images/%s", name);

    file = fopen(filename, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nFile not found.");
        return;
    }

    fseek(file, 0L, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0L, SEEK_SET);

    printf("HTTP/1.1 200 OK\r\nContent-Length: %ld\r\nConnection: close\r\n", filesize);

    // Determine Content-Type based on file extension
    const char *ext = strrchr(name, '.');
    if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0) {
        printf("Content-Type: image/jpeg\r\n");
    } else if (strcmp(ext, ".png") == 0) {
        printf("Content-Type: image/png\r\n");
    } else if (strcmp(ext, ".gif") == 0) {
        printf("Content-Type: image/gif\r\n");
    } else {
        printf("Content-Type: application/octet-stream\r\n");
    }

    printf("\r\n");

    char buffer[4096];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, sizeof(char), sizeof(buffer), file)) > 0) {
        fwrite(buffer, sizeof(char), bytes_read, stdout);
    }

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