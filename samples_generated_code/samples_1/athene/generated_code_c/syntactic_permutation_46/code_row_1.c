#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *url;
    void (*handler)(const char *);
} Route;

void not_found() {
    printf("HTTP/1.1 404 Not Found\r\n");
    printf("Content-Type: text/plain; charset=UTF-8\r\n");
    printf("\r\n");
    printf("Not Found");
}

void img(const char *name) {
    FILE *file = fopen(name, "rb");
    if (file == NULL) {
        not_found();
        return;
    }
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: image/jpeg\r\n");
    printf("\r\n");

    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }
    fclose(file);
}

void dispatch_request(const Route routes[], int num_routes, const char *url) {
    for (int i = 0; i < num_routes; ++i) {
        if (strcmp(routes[i].url, url) == 0) {
            routes[i].handler(url + strlen("/img/"));
            return;
        }
    }
    not_found();
}

int main() {
    Route routes[] = {{"^/img/(.*)$", img}};
    const char *request_url = "/img/example.jpg"; // This would come from the actual request in a real server
    dispatch_request(routes, 1, request_url);
    return 0;
}