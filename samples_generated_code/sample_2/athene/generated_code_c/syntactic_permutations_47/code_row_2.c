#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAX_PATH 256

void send_file_to_browser(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<h1>File Not Found</h1>");
        return;
    }

    struct stat file_stat;
    fstat(fileno(file), &file_stat);

    printf("HTTP/1.1 200 OK\r\n");
    if (strcasestr(filename, ".jpg") || strcasestr(filename, ".jpeg")) {
        printf("Content-Type: image/jpeg\r\n");
    } else if (strcasestr(filename, ".png")) {
        printf("Content-Type: image/png\r\n");
    } else if (strcasetr(filename, ".gif")) {
        printf("Content-Type: image/gif\r\n");
    } else {
        printf("Content-Type: application/octet-stream\r\n");
    }
    printf("Content-Length: %ld\r\n", file_stat.st_size);
    printf("\r\n");

    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }

    fclose(file);
}

void url_exists(const char *url) {
    char path[MAX_PATH];
    snprintf(path, MAX_PATH, "images/%s", url);

    if (access(path, F_OK) == 0) {
        send_file_to_browser(path);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<h1>File Not Found</h1>");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }

    url_exists(argv[1]);

    return 0;
}