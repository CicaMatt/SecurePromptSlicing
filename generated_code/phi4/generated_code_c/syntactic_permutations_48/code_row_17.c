#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void img(char *file) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", "./images/", file);

    FILE *fp = fopen(filepath, "rb");
    if (fp == NULL) {
        printf("HTTP/1.0 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\n");
        return;
    }

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *data = malloc(fsize + 1);
    if (data == NULL) {
        fclose(fp);
        printf("HTTP/1.0 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nMemory allocation failed.\n");
        return;
    }

    fread(data, 1, fsize, fp);
    data[fsize] = '\0';

    char *mimetype = "application/octet-stream";
    if (strcmp(file + strlen(file) - 3, "jpg") == 0 || strcmp(file + strlen(file) - 4, "jpeg") == 0) {
        mimetype = "image/jpeg";
    } else if (strcmp(file + strlen(file) - 3, "png") == 0) {
        mimetype = "image/png";
    }

    printf("HTTP/1.0 200 OK\r\nContent-Type: %s\r\nContent-Length: %ld\r\n\r\n", mimetype, fsize);
    fwrite(data, 1, fsize, stdout);

    free(data);
    fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    img(argv[1]);

    return 0;
}