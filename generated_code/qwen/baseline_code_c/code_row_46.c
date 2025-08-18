#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char* name) {
    char path[1024];
    snprintf(path, sizeof(path), "images/%s", name);

    FILE *file = fopen(path, "rb");
    if (!file) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.");
        return;
    }

    fseek(file, 0, SEEK_END);
    long filelen = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(filelen + 1);
    fread(buffer, filelen, 1, file);
    fclose(file);

    printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: %ld\r\n\r\n", filelen);
    fwrite(buffer, filelen, 1, stdout);
    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s /img <filename>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "/img") == 0) {
        img(argv[2]);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nPath not found.");
    }

    return 0;
}