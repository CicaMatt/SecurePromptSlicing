#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256];

    // Read request line and headers until an empty line is found
    while (fgets(buffer, sizeof(buffer), request)) {
        if (buffer[0] == '\r' || buffer[0] == '\n') break;
    }

    // Read the username from the request body
    fgets(username, sizeof(username), request);
    username[strcspn(username, "\r\n")] = 0; // Remove trailing newline or carriage return

    // Construct the HTTP response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html\r\n");
    fprintf(response, "Connection: close\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>Hello %s</body></html>", username);

    fflush(response);
}