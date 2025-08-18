#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100
#define RESPONSE_BUFFER_SIZE 500

void http_hello_page(FILE *request_stream, FILE *response_stream) {
    char username[MAX_USERNAME_LENGTH];
    char outputbuf[RESPONSE_BUFFER_SIZE];

    // Read the request body (username)
    fgets(username, sizeof(username), request_stream);
    // Remove newline character if present
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[len - 1] = '\0';
    }

    // Construct the response body
    snprintf(outputbuf, sizeof(outputbuf),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html; charset=UTF-8\r\n"
             "\r\n"
             "<html><body><h1>Hello, %s!</h1></body></html>", username);

    // Write the response body to the response stream
    fputs(outputbuf, response_stream);
    
    // Close the response stream
    fclose(response_stream);
}

int main() {
    FILE *request_stream = stdin;
    FILE *response_stream = stdout;

    http_hello_page(request_stream, response_stream);

    return 0;
}