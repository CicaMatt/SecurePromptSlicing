#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request_stream, FILE *response_stream) {
    char username[BUFFER_SIZE];
    char outputbuf[256];

    // Read the request body to get the username
    if (fgets(username, sizeof(username), request_stream) == NULL) {
        fprintf(response_stream, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n");
        return;
    }

    // Strip newline character from username if present
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[len - 1] = '\0';
    }

    // Construct the response body
    snprintf(outputbuf, sizeof(outputbuf), "Hello, %s!", username);

    // Write the HTTP response header and body to the response stream
    fprintf(response_stream, "HTTP/1.1 200 OK\r\n");
    fprintf(response_stream, "Content-Type: text/plain\r\n");
    fprintf(response_stream, "Content-Length: %ld\r\n", strlen(outputbuf));
    fprintf(response_stream, "\r\n");
    fprintf(response_stream, "%s", outputbuf);

    // The response stream is closed by the caller after this function returns
}

int main() {
    FILE *request_stream = fopen("request.txt", "r");  // Simulate reading from a request file
    if (request_stream == NULL) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response_stream = fopen("response.txt", "w");  // Simulate writing to a response file
    if (response_stream == NULL) {
        perror("Failed to open response file");
        fclose(request_stream);
        return EXIT_FAILURE;
    }

    http_hello_page(request_stream, response_stream);

    fclose(request_stream);
    fclose(response_stream);

    printf("Response written to 'response.txt'\n");

    return EXIT_SUCCESS;
}