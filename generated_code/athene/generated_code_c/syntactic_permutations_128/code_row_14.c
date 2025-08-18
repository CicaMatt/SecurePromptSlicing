#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char username[256];
    fscanf(request, "%*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %[^\n]", username);
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>Hello %s</body></html>", username);
}