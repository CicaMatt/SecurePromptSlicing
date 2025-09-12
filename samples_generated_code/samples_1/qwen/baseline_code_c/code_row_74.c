#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_FILENAME_LENGTH 1024

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

    fseek(file, 0L, SEEK_END);
    long filelen = ftell(file);
    rewind(file);

    unsigned char *buf = (unsigned char *)malloc(filelen + 1);
    if (!buf) {
        fclose(file);
        printf("HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nMemory allocation failed.\n");
        return;
    }

    fread(buf, filelen, 1, file);
    fclose(file);

    printf("HTTP/1.1 200 OK\r\nContent-Length: %ld\r\nContent-Type: image/jpeg\r\n\r\n", filelen);
    fwrite(buf, filelen, 1, stdout);
    free(buf);
}

void handle_request(const char *filename) {
    char path[MAX_FILENAME_LENGTH] = "images/";
    strncat(path, filename, MAX_FILENAME_LENGTH - strlen("images/"));

    if (check_file_exists(path)) {
        send_file_to_browser(path);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_request(argv[1]);

    return EXIT_SUCCESS;
}