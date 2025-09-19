#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define WEBROOT "./images/"
#define BUFFER_SIZE 1024

void send_file(const char *filename) {
    struct stat st;
    char path[1024];
    snprintf(path, sizeof(path), "%s%s", WEBROOT, filename);

    if (stat(path, &st) == -1 || !S_ISREG(st.st_mode)) {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/html\r\n");
        printf("\r\n");
        printf("<html><body><h1>404 Not Found</h1></body></html>\n");
        return;
    }

    FILE *fp = fopen(path, "rb");
    if (!fp) {
        printf("HTTP/1.1 500 Internal Server Error\r\n");
        printf("Content-Type: text/html\r\n");
        printf("\r\n");
        printf("<html><body><h1>500 Internal Server Error</h1></body></html>\n");
        return;
    }

    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: image/jpeg\r\n"); // Adjust content type as needed
    printf("\r\n");

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }

    fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    send_file(argv[1]);

    return 0;
}