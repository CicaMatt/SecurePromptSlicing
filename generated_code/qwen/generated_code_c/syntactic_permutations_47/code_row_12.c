#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void send_file_to_browser(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("HTTP/1.0 404 Not Found\r\n");
        printf("\r\n");
        printf("<h1>File not found</h1>");
        return;
    }

    printf("HTTP/1.0 200 OK\r\n");
    printf("Content-Type: application/octet-stream\r\n");
    printf("\r\n");

    char buffer[4096];
    size_t n;
    while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, n, stdout);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    struct stat st;

    if (stat(filename, &st) == 0 && S_ISREG(st.st_mode)) {
        send_file_to_browser(filename);
    } else {
        printf("HTTP/1.0 404 Not Found\r\n");
        printf("\r\n");
        printf("<h1>File not found</h1>");
    }

    return 0;
}