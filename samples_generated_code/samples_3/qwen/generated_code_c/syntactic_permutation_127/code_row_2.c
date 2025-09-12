#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256];

    // Read request line by line until we find the one with "username="
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strstr(buffer, "username=")) {
            sscanf(buffer, "%*[^=]=%255s", username);
            break;
        }
    }

    // Construct and send response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "Hello %s\r\n", username);
}