#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256] = "";
    fscanf(request, "%*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s username=%255[^\n]", username);
    fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    fprintf(response, "<html><body>Hello %s</body></html>", username);
}