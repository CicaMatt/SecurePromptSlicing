#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256];

    // Read request line by line until we find "username="
    while (fgets(buffer, sizeof(buffer), request)) {
        if (sscanf(buffer, "username=%s", username) == 1) {
            break;
        }
    }

    // Construct the HTTP response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "\r\n"); // End of headers
    fprintf(response, "Hello %s", username);

    fflush(response);
}