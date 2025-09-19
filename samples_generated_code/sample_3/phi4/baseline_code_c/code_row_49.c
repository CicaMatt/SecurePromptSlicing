#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

void send_response(FILE *file, const char *filename) {
    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n");
        printf("<html><body><h1>File not found</h1></body></html>");
    } else {
        printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\n\r\n");

        while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
            fwrite(buffer, 1, bytes_read, stdout);
        }

        fclose(file);
    }
}

void img(const char *url) {
    if (strncmp(url, "/img/", 5) == 0) {
        const char *filename = url + 5;
        FILE *file = fopen(filename, "rb");

        send_response(file, filename);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n");
        printf("<html><body><h1>Not Found</h1></body></html>");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    img(argv[1]);

    return EXIT_SUCCESS;
}