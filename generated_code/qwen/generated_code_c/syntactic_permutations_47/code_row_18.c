#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_FILENAME_LEN 256

void send_file_to_browser(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nFile not found.");
        return;
    }

    fseek(file, 0L, SEEK_END);
    long filelen = ftell(file);
    fseek(file, 0L, SEEK_SET);

    printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: %ld\r\nConnection: close\r\n\r\n", filelen);
    char *buffer = (char *)malloc(filelen + 1);
    fread(buffer, filelen, 1, file);
    fclose(file);

    fwrite(buffer, filelen, 1, stdout);
    free(buffer);
}

int file_exists(const char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

void handle_request(const char *url_path) {
    char filename[MAX_FILENAME_LEN];
    snprintf(filename, sizeof(filename), "images/%s", url_path);

    if (file_exists(filename)) {
        send_file_to_browser(filename);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nFile not found.");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_request(argv[1]);

    return EXIT_SUCCESS;
}