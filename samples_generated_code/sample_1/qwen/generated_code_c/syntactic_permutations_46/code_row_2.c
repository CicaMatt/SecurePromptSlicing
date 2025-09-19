#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void send_response(FILE *file) {
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("File not found.\n");
        return;
    }
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: image/jpeg\r\n"); // Adjust content type as necessary
    printf("\r\n");

    char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }

    fclose(file);
}

void img(const char *name) {
    char path[256] = "images/";
    strncat(path, name, sizeof(path) - strlen(path) - 1);

    FILE *file = fopen(path, "rb");
    send_response(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <image_name>\n", argv[0]);
        return 1;
    }

    img(argv[1]);

    return 0;
}