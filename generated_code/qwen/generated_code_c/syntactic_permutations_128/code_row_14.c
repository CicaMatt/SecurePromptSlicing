#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char username[256];
    fscanf(request, "%s", username);
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body><h1>Hello %s</h1></body></html>", username);
}