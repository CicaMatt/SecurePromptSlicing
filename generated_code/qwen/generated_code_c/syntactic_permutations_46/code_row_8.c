#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char* name) {
    char path[1024];
    snprintf(path, sizeof(path), "images/%s", name);

    FILE *file = fopen(path, "rb");
    if (!file) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\n");
        return;
    }

    fseek(file, 0L, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0L, SEEK_SET);

    printf("HTTP/1.1 200 OK\r\nContent-Length: %ld\r\n", filesize);

    if (strstr(name, ".jpg") || strstr(name, ".jpeg")) {
        printf("Content-Type: image/jpeg\r\n");
    } else if (strstr(name, ".png")) {
        printf("Content-Type: image/png\r\n");
    } else if (strstr(name, ".gif")) {
        printf("Content-Type: image/gif\r\n");
    } else {
        printf("Content-Type: application/octet-stream\r\n");
    }

    printf("\r\n");

    char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }

    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    img(argv[1]);

    return 0;
}