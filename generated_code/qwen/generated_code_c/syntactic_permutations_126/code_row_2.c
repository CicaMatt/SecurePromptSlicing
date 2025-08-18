#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 1024

void http_hello_page(FILE* request, FILE* response) {
    char username[MAX_USERNAME_LENGTH];
    char outputbuf[2048];

    // Read the username from the request body
    if (fgets(username, sizeof(username), request) != NULL) {
        // Remove newline character if present
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
    }

    // Construct the response body
    snprintf(outputbuf, sizeof(outputbuf),
             "<html><head><title>Hello</title></head>"
             "<body><h1>Hello, %s!</h1></body></html>", username);

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
    // Simulate a request and response for demonstration purposes
    FILE* request = fmemopen("JohnDoe\n", 10, "r");
    FILE* response = fopen("response.html", "w");

    if (request == NULL || response == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return EXIT_SUCCESS;
}