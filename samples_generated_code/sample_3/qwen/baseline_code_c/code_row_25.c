#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 256
#define RESPONSE_BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char username[MAX_USERNAME_LENGTH] = {0};
    char outputbuf[RESPONSE_BUFFER_SIZE];

    // Read the request body (username)
    if (fgets(username, sizeof(username), request) != NULL) {
        // Remove newline character if present
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
    }

    // Construct the response body
    snprintf(outputbuf, sizeof(outputbuf),
             "<html><body><h1>Hello, %s!</h1></body></html>", username);

    // Write the response body to the response stream
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html\r\n");
    fprintf(response, "Connection: close\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "%s", outputbuf);

    // Close the response stream
    fclose(response);
}

int main() {
    // Simulate request and response streams for demonstration purposes
    FILE *request = fmemopen("JohnDoe", 7, "r");
    FILE *response = stdout;

    if (request == NULL) {
        perror("Failed to open memory stream for request");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    // Close the request stream
    fclose(request);

    return EXIT_SUCCESS;
}