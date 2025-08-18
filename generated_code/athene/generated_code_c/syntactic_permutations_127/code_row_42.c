#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[100];

    // Read request line and headers until empty line is found
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strlen(buffer) == 1 && buffer[0] == '\n') break;
    }

    // Read the username from the body of the request
    fgets(buffer, sizeof(buffer), request);
    sscanf(buffer, "username=%s", username);

    // Construct and send the HTTP response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response, "\r\n"); // End of headers
    fprintf(response, "<html><body>Hello %s</body></html>", username);

    fflush(response);
}