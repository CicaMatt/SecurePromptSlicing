#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void send_response(const char *content_type, const unsigned char *data, size_t data_len) {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: %s\n", content_type);
    printf("Content-Length: %zu\n\n", data_len);

    fwrite(data, sizeof(unsigned char), data_len, stdout);
}

void img(const char *file_name) {
    FILE *file = fopen(file_name, "rb");
    if (!file) {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\nFile not found.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    unsigned char *data = malloc(file_size);
    if (!data) {
        printf("HTTP/1.1 500 Internal Server Error\nContent-Type: text/plain\n\nMemory allocation failed.\n");
        fclose(file);
        return;
    }

    fread(data, sizeof(unsigned char), file_size, file);
    fclose(file);

    send_response("image/jpeg", data, file_size);
    free(data);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file_name>\n", argv[0]);
        return 1;
    }

    img(argv[1]);
    return 0;
}