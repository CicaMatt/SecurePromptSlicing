#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char inputbuf[1024];
    char outputbuf[] = "<html><body><h1>Hello, World!</h1></body></html>";

    // Read the request body (assuming it's not needed for this simple response)
    while (fgets(inputbuf, sizeof(inputbuf), request) != NULL) {
        if (strcmp(inputbuf, "\r\n") == 0 || strcmp(inputbuf, "\n") == 0) {
            break; // End of headers
        }
    }

    // Write the response body to the response stream
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html\r\n");
    fprintf(response, "Content-Length: %zu\r\n", strlen(outputbuf));
    fprintf(response, "\r\n"); // End of headers
    fprintf(response, "%s", outputbuf);

    // Close the response stream
    fclose(response);
}