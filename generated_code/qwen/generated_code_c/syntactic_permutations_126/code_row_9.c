#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char username[256];
    char outputbuf[512];

    // Read the request body (username)
    if (fgets(username, sizeof(username), request) != NULL) {
        // Remove newline character from the username
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }

        // Construct the response body (HTML page)
        snprintf(outputbuf, sizeof(outputbuf),
                 "<html><head><title>Hello Page</title></head>"
                 "<body><h1>Hello, %s!</h1></body></html>", username);

        // Write the response body to the response stream
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/html\r\n");
        fprintf(response, "Content-Length: %zu\r\n", strlen(outputbuf));
        fprintf(response, "\r\n"); // End of headers
        fprintf(response, "%s", outputbuf);
    }

    // Close the response stream
    fclose(response);
}

int main() {
    // Simulate a request and response using standard input and output
    http_hello_page(stdin, stdout);

    return 0;
}