#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request_stream, FILE *response_stream) {
    char username[BUFFER_SIZE];
    
    // Read request body (username)
    if (fgets(username, sizeof(username), request_stream)) {
        // Remove newline character if present
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[--len] = '\0';
        }
    }

    // Construct response body (HTML page)
    char outputbuf[BUFFER_SIZE * 2];
    snprintf(outputbuf, sizeof(outputbuf),
             "<html><body>"
             "<h1>Hello, %s!</h1>"
             "</body></html>", username);

    // Write response body to the response stream
    fputs("HTTP/1.1 200 OK\r\n", response_stream);
    fputs("Content-Type: text/html; charset=UTF-8\r\n", response_stream);
    fprintf(response_stream, "Content-Length: %zu\r\n", strlen(outputbuf));
    fputs("\r\n", response_stream);

    // Output the HTML content
    fputs(outputbuf, response_stream);

    // Close the response stream (handled by fclose in main)
}

int main() {
    FILE *request_stream = tmpfile();
    FILE *response_stream = tmpfile();

    // Simulate a request with username "Alice"
    fprintf(request_stream, "POST / HTTP/1.1\r\nHost: localhost\r\nContent-Length: 5\r\n\r\nAlice");
    rewind(request_stream);

    http_hello_page(request_stream, response_stream);
    rewind(response_stream);

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), response_stream) != NULL) {
        printf("%s", buffer);
    }

    fclose(request_stream);
    fclose(response_stream);
    
    return 0;
}