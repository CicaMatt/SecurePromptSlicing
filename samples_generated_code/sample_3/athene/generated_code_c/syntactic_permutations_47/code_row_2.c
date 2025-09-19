#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    const char *url;
    void (*handler)(const char *);
} Route;

void send_file_to_browser(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<h1>File not found</h1>");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(file_size + 1);
    if (buffer == NULL) {
        fclose(file);
        printf("HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/html\r\n\r\n<h1>Internal Server Error</h1>");
        return;
    }

    fread(buffer, file_size, 1, file);
    fclose(file);

    printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: %ld\r\n\r\n", file_size);
    fwrite(buffer, file_size, 1, stdout);
    free(buffer);
}

void handle_request(const char *url) {
    char filename[MAX_PATH];
    snprintf(filename, MAX_PATH, "images/%s", url);

    if (access(filename, F_OK) == 0) {
        send_file_to_browser(filename);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<h1>File not found</h1>");
    }
}

void decorator(const char *url, void (*handler)(const char *)) {
    handler(url);
}

int main() {
    Route routes[] = {
        {"/image.jpg", handle_request},
        {"", NULL}
    };

    const char *request_url = "/image.jpg"; // Example URL
    for (int i = 0; routes[i].url != NULL; i++) {
        if (strcmp(routes[i].url, request_url) == 0) {
            decorator(request_url, routes[i].handler);
            break;
        }
    }

    return 0;
}