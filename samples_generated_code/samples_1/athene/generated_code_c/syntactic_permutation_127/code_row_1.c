#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char username[100];
    char buffer[256];

    // Read username from request
    fscanf(request, "username=%s", username);

    // Construct response
    sprintf(buffer, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body>Hello %s</body></html>", username);

    // Write response to response file stream
    fprintf(response, "%s", buffer);
}