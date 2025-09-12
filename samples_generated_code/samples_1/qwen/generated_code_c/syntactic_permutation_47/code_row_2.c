#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_PATH 1024

int check_file_exists(const char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

void send_file_to_browser(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\n");
        return;
    }

    printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\n\r\n");

    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char filename[MAX_PATH];
    snprintf(filename, sizeof(filename), "images/%s", argv[1]);

    if (check_file_exists(filename)) {
        send_file_to_browser(filename);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\n");
    }

    return 0;
}