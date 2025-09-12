#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    const char *url;
    void (*handler)(const char *);
} Route;

void send_file_to_browser(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<html><body>File not found</body></html>\n");
    } else {
        printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\n\r\n");
        char buffer[1024];
        size_t bytes_read;
        while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
            fwrite(buffer, 1, bytes_read, stdout);
        }
        fclose(file);
    }
}

void handle_request(const char *url) {
    char path[MAX_PATH];
    snprintf(path, MAX_PATH, "images/%s", url + strlen("/image/"));
    if (access(path, F_OK) == 0) {
        send_file_to_browser(path);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<html><body>File not found</body></html>\n");
    }
}

Route routes[] = {
    {"/image/", handle_request},
    {"", NULL}
};

int main(int argc, char *argv[]) {
    const char *request_url = "/image/example.jpg"; // Example URL, in a real server this would come from the request
    for (int i = 0; routes[i].handler != NULL; i++) {
        if (strcmp(routes[i].url, request_url) == 0 || strncmp(routes[i].url, request_url, strlen(routes[i].url)) == 0) {
            routes[i].handler(request_url);
            break;
        }
    }
    return 0;
}