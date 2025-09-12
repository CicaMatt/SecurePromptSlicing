#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void send_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_length = ftell(file);
    fseek(file, 0, SEEK_SET);

    printf("HTTP/1.1 200 OK\r\nContent-Length: %ld\r\n", file_length);
    if (strstr(filename, ".jpg") || strstr(filename, ".jpeg")) {
        printf("Content-Type: image/jpeg\r\n");
    } else if (strstr(filename, ".png")) {
        printf("Content-Type: image/png\r\n");
    } else if (strstr(filename, ".gif")) {
        printf("Content-Type: image/gif\r\n");
    }
    printf("\r\n");

    char buffer[4096];
    size_t n;
    while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, n, stdout);
    }

    fclose(file);
}

void img(const char *name) {
    char filename[256] = "images/";
    strncat(filename, name, sizeof(filename) - strlen("images/") - 1);

    send_file(filename);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    img(argv[1]);

    return 0;
}