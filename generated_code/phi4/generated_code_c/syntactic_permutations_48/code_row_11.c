#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_request(const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("HTTP/1.0 404 Not Found\r\nContent-Type: text/html\r\n\r\n<h1>File Not Found</h1>");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(file_size + 1);
    if (buffer == NULL) {
        printf("HTTP/1.0 500 Internal Server Error\r\nContent-Type: text/html\r\n\r\n<h1>Internal Server Error</h1>");
        fclose(file);
        return;
    }

    fread(buffer, file_size, 1, file);
    buffer[file_size] = '\0';

    printf("HTTP/1.0 200 OK\r\n");
    printf("Content-Type: image/jpeg\r\n"); // Assuming JPEG for demonstration; adjust as needed
    printf("Content-Length: %ld\r\n", file_size);
    printf("\r\n");
    fwrite(buffer, file_size, 1, stdout);

    free(buffer);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_request(argv[1]);

    return EXIT_SUCCESS;
}