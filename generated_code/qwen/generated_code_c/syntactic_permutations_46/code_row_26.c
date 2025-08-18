#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char *name) {
    FILE *file;
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "images/%s", name);

    file = fopen(filepath, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nFile not found.");
        return;
    }

    fseek(file, 0L, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0L, SEEK_SET);

    printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: %ld\r\nConnection: close\r\n\r\n", filesize);

    char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
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