#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char username[1024];
    fscanf(request, "username=%s", username);
    fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    fprintf(response, "<html><body>Hello %s</body></html>", username);
}