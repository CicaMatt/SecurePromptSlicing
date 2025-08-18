#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char* name) {
    FILE *file;
    char path[1024];
    snprintf(path, sizeof(path), "images/%s", name);
    
    file = fopen(path, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("File not found.\n");
        return;
    }

    fseek(file, 0L, SEEK_END);
    long size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL) {
        printf("HTTP/1.1 500 Internal Server Error\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Memory allocation failed.\n");
        fclose(file);
        return;
    }

    fread(buffer, size, 1, file);
    buffer[size] = '\0';

    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: image/jpeg\r\n"); // Adjust content type as needed
    printf("Content-Length: %ld\r\n", size);
    printf("\r\n");

    fwrite(buffer, sizeof(char), size, stdout);

    free(buffer);
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