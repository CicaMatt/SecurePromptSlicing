#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define IMAGE_FOLDER "images/"
#define BUFFER_SIZE 4096

void send_file_to_browser(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nFile not found.\n");
        return;
    }

    struct stat file_stat;
    if (stat(filename, &file_stat) != 0) {
        printf("HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nInternal server error.\n");
        fclose(file);
        return;
    }

    char content_type[64] = "text/plain";
    if (strstr(filename, ".jpg") || strstr(filename, ".jpeg")) {
        strcpy(content_type, "image/jpeg");
    } else if (strstr(filename, ".png")) {
        strcpy(content_type, "image/png");
    } else if (strstr(filename, ".gif")) {
        strcpy(content_type, "image/gif");
    }

    printf("HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %ld\r\nConnection: close\r\n\r\n", content_type, file_stat.st_size);

    char buffer[BUFFER_SIZE];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char filename[256];
    snprintf(filename, sizeof(filename), "%s%s", IMAGE_FOLDER, argv[1]);

    struct stat file_stat;
    if (stat(filename, &file_stat) == 0 && S_ISREG(file_stat.st_mode)) {
        send_file_to_browser(filename);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nFile not found.\n");
    }

    return 0;
}