#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char name[256] = "";
    int content_length = 0;
    size_t n;

    while (fgets(buffer, sizeof(buffer), request)) {
        if (sscanf(buffer, "Content-Length: %d", &content_length) == 1) break;
    }

    if (content_length > 0 && content_length < sizeof(name)) {
        fread(name, 1, content_length, request);
        name[content_length] = '\0';
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html\r\n");
    fprintf(response, "Connection: close\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>Hello %s</body></html>", name);
}