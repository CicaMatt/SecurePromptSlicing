#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 100
#define OUTPUT_BUFFER_SIZE 500

void handleHelloRequest(FILE *requestStream, FILE *responseStream) {
    char username[MAX_USERNAME_LENGTH];
    char outputbuf[OUTPUT_BUFFER_SIZE];

    // Read the request body (username)
    if (fgets(username, sizeof(username), requestStream) != NULL) {
        // Remove newline character from username if present
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }

        // Construct the response body
        snprintf(outputbuf, sizeof(outputbuf),
                 "<html><body><h1>Hello, %s!</h1></body></html>", username);

        // Write the response body to the response stream
        fprintf(responseStream, "HTTP/1.1 200 OK\r\n");
        fprintf(responseStream, "Content-Type: text/html\r\n");
        fprintf(responseStream, "Content-Length: %zu\r\n", strlen(outputbuf));
        fprintf(responseStream, "\r\n"); // End of headers
        fprintf(responseStream, "%s", outputbuf);

        // Close the response stream
        fclose(responseStream);
    }
}

int main() {
    // Simulate a server request and response using standard input and output
    handleHelloRequest(stdin, stdout);

    return 0;
}