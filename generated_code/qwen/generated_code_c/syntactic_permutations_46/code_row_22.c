#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char* name) {
    char path[1024];
    snprintf(path, sizeof(path), "images/%s", name);

    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nContent-Length: 13\r\n\r\nFile not found.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileLen = ftell(file);
    fseek(file, 0, SEEK_SET);

    printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: %ld\r\n\r\n", fileLen);

    char *buffer = (char *)malloc(fileLen + 1);
    fread(buffer, fileLen, 1, file);
    fclose(file);

    fwrite(buffer, fileLen, 1, stdout);
    free(buffer);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    img(argv[1]);

    return 0;
}