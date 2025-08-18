#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[100];

    // Read request line and headers until an empty line is found
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strcmp(buffer, "\r\n") == 0) break; // End of headers
    }

    // Assuming the username is passed as a query parameter in GET request like "username=John"
    fgets(buffer, sizeof(buffer), request);
    sscanf(buffer, "username=%s", username);

    // Construct the HTTP response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><head><title>Hello</title></head><body>\n");
    fprintf(response, "Hello %s!\n", username);
    fprintf(response, "</body></html>\n");

    fflush(response);
}