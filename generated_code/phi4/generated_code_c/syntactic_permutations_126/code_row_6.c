#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void process_request(const char *request_body, char *outputbuf) {
    // Construct the response body (HTML page)
    snprintf(outputbuf, BUFFER_SIZE, "<html><body><h1>Welcome, %s!</h1></body></html>", request_body);
}

int main() {
    FILE *stream = NULL;
    char request_body[BUFFER_SIZE] = {0};
    char outputbuf[BUFFER_SIZE] = {0};

    // Simulate reading the request body
    printf("Enter username: ");
    if (fgets(request_body, BUFFER_SIZE, stdin) != NULL) {
        // Remove newline character from request body if present
        size_t len = strlen(request_body);
        if (len > 0 && request_body[len - 1] == '\n') {
            request_body[--len] = '\0';
        }

        // Process the request and construct response
        process_request(request_body, outputbuf);

        // Simulate writing the response body to a file stream as response
        stream = fopen("response.html", "w");
        if (stream != NULL) {
            fputs(outputbuf, stream);
            fclose(stream);  // Close the response stream

            printf("\nResponse written to 'response.html'\n");
        } else {
            perror("Failed to open file for writing response");
        }
    }

    return 0;
}