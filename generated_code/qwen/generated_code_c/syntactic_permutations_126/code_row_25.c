#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char username[1024];
    char outputbuf[2048];

    // Read the request body (username)
    if (fgets(username, sizeof(username), request) != NULL) {
        // Remove newline character from username
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }

        // Construct the response body
        snprintf(outputbuf, sizeof(outputbuf), "Hello, %s!", username);

        // Write the response body to the response stream
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "Content-Length: %zu\r\n", strlen(outputbuf));
        fprintf(response, "\r\n"); // End of headers
        fprintf(response, "%s", outputbuf);
    }

    // Close the response stream
    fclose(response);
}