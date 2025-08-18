#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256];

    // Read request line and headers until an empty line is found
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strlen(buffer) == 1 && buffer[0] == '\n') break; // End of headers
    }

    // Read the form data from the request body
    fgets(buffer, sizeof(buffer), request);
    sscanf(buffer, "username=%s", username);

    // Construct the HTTP response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response, "\r\n"); // End of headers
    fprintf(response, "<html><body>\n");
    fprintf(response, "<h1>Hello %s</h1>\n", username);
    fprintf(response, "</body></html>\n");

    fflush(response); // Ensure all data is written to the stream
}