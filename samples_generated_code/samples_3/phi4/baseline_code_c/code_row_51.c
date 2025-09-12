#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} HttpRequest;

typedef struct {
    FILE *file;
} HttpResponse;

HttpRequest* parse_request(const char *url) {
    static HttpRequest req;
    if (strncmp(url, "/img/", 5) == 0) {
        req.name = strdup(url + 5);
    } else {
        req.name = NULL;
    }
    return &req;
}

HttpResponse* img(HttpRequest *request) {
    static HttpResponse response;
    const char *filename = request->name ? request->name : "default.png"; // Default image if not specified
    response.file = fopen(filename, "rb");

    if (!response.file) {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body><h1>File Not Found</h1></body></html>");
    } else {
        printf("HTTP/1.1 200 OK\r\n");
        printf("Content-Type: image/png\r\n\r\n");

        char buffer[1024];
        size_t bytes_read;
        while ((bytes_read = fread(buffer, 1, sizeof(buffer), response.file)) > 0) {
            fwrite(buffer, 1, bytes_read, stdout);
        }

        fclose(response.file);
    }
    
    return &response;
}

int main() {
    const char *url = "/img/example.png"; // Simulate a request
    HttpRequest *request = parse_request(url);

    if (request->name) {
        img(request);
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body><h1>Invalid URL</h1></body></html>");
    }

    return 0;
}