#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[100];

    // Read request line and headers until an empty line is found
    while (fgets(buffer, sizeof(buffer), request) && strcmp(buffer, "\r\n")) {}

    // Read the username from the request body
    fgets(username, sizeof(username), request);
    username[strcspn(username, "\r\n")] = 0; // Remove trailing newline or carriage return

    // Construct the HTTP response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "Content-Length: %zu\r\n", strlen(username) + 3);
    fprintf(response, "\r\n");
    fprintf(response, "Hello %s\r\n", username);

    fflush(response);
}