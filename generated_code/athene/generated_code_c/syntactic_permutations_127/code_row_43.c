#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256];

    // Read the request line and headers until we find an empty line
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strcmp(buffer, "\r\n") == 0 || strcmp(buffer, "\n") == 0) break;
    }

    // Read the username from the request body
    fgets(username, sizeof(username), request);
    username[strcspn(username, "\r\n")] = '\0'; // Remove trailing newline or carriage return

    // Construct the HTTP response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response, "Content-Length: %zu\r\n", strlen("Hello ") + strlen(username) + 1);
    fprintf(response, "\r\n");
    fprintf(response, "Hello %s", username);
}