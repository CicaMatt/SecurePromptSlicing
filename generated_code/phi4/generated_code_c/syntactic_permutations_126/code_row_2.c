#include <stdio.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

void http_hello_page(FILE *response_stream) {
    char username[MAX_BUFFER_SIZE];
    char outputbuf[MAX_BUFFER_SIZE];

    // Simulate reading a request body (username)
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);

    // Remove newline character from the input
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[len - 1] = '\0';
    }

    // Construct the response body (HTML page)
    snprintf(outputbuf, sizeof(outputbuf),
             "<html><body><h1>Hello, %s!</h1></body></html>", username);

    // Write the response body to the response stream
    fprintf(response_stream, "HTTP/1.1 200 OK\r\n");
    fprintf(response_stream, "Content-Type: text/html\r\n");
    fprintf(response_stream, "Content-Length: %zu\r\n", strlen(outputbuf));
    fprintf(response_stream, "\r\n"); // End of headers
    fputs(outputbuf, response_stream);

    // Flush the stream to ensure all data is written
    fflush(response_stream);
}

int main() {
    FILE *response_stream = stdout; // Using standard output for demonstration

    http_hello_page(response_stream);

    return 0;
}