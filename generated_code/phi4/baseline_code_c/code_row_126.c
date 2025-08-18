#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 256
#define RESPONSE_BUFFER_SIZE 1024

void http_hello_page(FILE *response_stream) {
    char username[MAX_USERNAME_LEN];
    
    // Simulating reading from a request body (here we use fgets for demonstration)
    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin)) {
        // Remove newline character if present
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
    }

    char outputbuf[RESPONSE_BUFFER_SIZE];
    
    // Constructing the response body
    snprintf(outputbuf, sizeof(outputbuf),
             "<html><body>"
             "<h1>Hello, %s!</h1>"
             "</body></html>", username);

    // Writing the response body to the response stream
    fputs("HTTP/1.1 200 OK\r\n", response_stream);
    fprintf(response_stream, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response_stream, "Content-Length: %zu\r\n", strlen(outputbuf));
    fputs("\r\n", response_stream); // End of headers

    // Write the HTML content
    fputs(outputbuf, response_stream);
    
    // Close the response stream (in a real server scenario, this would be handled differently)
}

int main() {
    FILE *response_stream = stdout; // Use standard output for demonstration
    
    http_hello_page(response_stream);

    return 0;
}