#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[100];

    // Read request line
    fgets(buffer, sizeof(buffer), request);
    if (sscanf(buffer, "GET /?username=%99[^&] ", username) == 1) {
        // Construct response headers
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/html\r\n");
        fprintf(response, "\r\n");

        // Construct HTML body with the username
        fprintf(response, "<html><body>Hello %s</body></html>", username);
    } else {
        // If username is not found, send a 400 Bad Request response
        fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
        fprintf(response, "Content-Type: text/html\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "<html><body>Bad Request</body></html>");
    }
}