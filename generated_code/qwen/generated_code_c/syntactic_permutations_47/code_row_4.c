#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define IMAGES_FOLDER "images/"
#define BUFFER_SIZE 1024

void send_file_to_browser(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\r\n");
        return;
    }

    struct stat file_stat;
    if (stat(filename, &file_stat) != 0) {
        fclose(file);
        printf("HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nInternal error.\r\n");
        return;
    }

    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Length: %ld\r\n", file_stat.st_size);
    printf("Content-Type: image/jpeg\r\n"); // Adjust the content type as necessary
    printf("\r\n");

    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\r\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    char file_path[FILENAME_MAX];
    snprintf(file_path, sizeof(file_path), "%s%s", IMAGES_FOLDER, filename);

    struct stat st;
    if (stat(file_path, &st) == 0 && S_ISREG(st.st_mode)) {
        send_file_to_browser(file_path);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\r\n");
    }

    return 0;
}