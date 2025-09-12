#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PATH 256

void send_file_to_browser(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>File not found</body></html>");
    } else {
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        rewind(file);

        char *buffer = malloc(file_size + 1);
        if (buffer != NULL) {
            fread(buffer, 1, file_size, file);
            fclose(file);

            printf("HTTP/1.1 200 OK\r\n");
            printf("Content-Type: image/jpeg\r\n"); // Assuming JPEG images
            printf("Content-Length: %ld\r\n", file_size);
            printf("\r\n");
            fwrite(buffer, 1, file_size, stdout);
            free(buffer);
        }
    }
}

void url_decorator(const char *url) {
    char path[MAX_PATH];
    snprintf(path, MAX_PATH, "images/%s", url);

    if (access(path, F_OK) == 0) {
        send_file_to_browser(path);
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>File not found</body></html>");
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    url_decorator(argv[1]);
    return 0;
}