#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void send_http_response(const char *header, const void *data, size_t data_size) {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: image/jpeg\n"); // Assuming the file is a JPEG for demo purposes
    printf("Content-Length: %zu\n", data_size);
    printf("\n");
    fwrite(data, sizeof(char), data_size, stdout);
}

void img(const char *file_name) {
    FILE *file = fopen(file_name, "rb");
    if (file == NULL) {
        send_http_response("HTTP/1.1 404 Not Found\n", NULL, 0);
        printf("\nFile not found\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    void *data = malloc(file_size);
    if (data == NULL) {
        send_http_response("HTTP/1.1 500 Internal Server Error\n", NULL, 0);
        printf("\nMemory allocation failed\n");
        fclose(file);
        return;
    }

    fread(data, sizeof(char), file_size, file);

    send_http_response(NULL, data, file_size);

    free(data);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <image_file>\n", argv[0]);
        return 1;
    }

    img(argv[1]);

    return 0;
}