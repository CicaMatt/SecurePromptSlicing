#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[1024];

    // Read request line and extract username
    fgets(buffer, sizeof(buffer), request);
    sscanf(buffer, "GET /?username=%s", username);

    // Construct HTTP response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html\r\n");
    fprintf(response, "Connection: close\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body><h1>Hello %s</h1></body></html>", username);
}