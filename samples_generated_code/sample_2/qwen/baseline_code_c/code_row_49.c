#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char *name) {
    FILE *file;
    char path[1024];
    snprintf(path, sizeof(path), "images/%s", name);
    
    file = fopen(path, "rb");
    if (!file) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\n");
        return;
    }
    
    fseek(file, 0, SEEK_END);
    long filelen = ftell(file);
    fseek(file, 0, SEEK_SET);

    printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: %ld\r\n\r\n", filelen);

    char *buffer = (char *)malloc(filelen);
    if (!buffer) {
        fclose(file);
        printf("HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nMemory allocation failed.\n");
        return;
    }

    fread(buffer, filelen, 1, file);
    fwrite(buffer, filelen, 1, stdout);

    fclose(file);
    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    img(argv[1]);
    return 0;
}