#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAX_NAME_LENGTH 1024

void img(const char *name) {
    char path[256] = "images/";
    FILE *file;
    struct stat file_stat;

    strncat(path, name, sizeof(path) - strlen(path) - 1);

    if (stat(path, &file_stat) == -1) {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n\r\n");
        printf("File not found.\n");
        return;
    }

    file = fopen(path, "rb");
    if (!file) {
        printf("HTTP/1.1 500 Internal Server Error\r\n");
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Could not open the file.\n");
        return;
    }

    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: image/jpeg\r\n"); // Adjust MIME type as necessary
    printf("Content-Length: %ld\r\n", file_stat.st_size);
    printf("\r\n");

    char buffer[4096];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    img(argv[1]);

    return EXIT_SUCCESS;
}