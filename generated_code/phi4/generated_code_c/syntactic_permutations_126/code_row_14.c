#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 256
#define RESPONSE_BUFFER_SIZE 1024

void http_hello_page(FILE *request_stream, FILE *response_stream) {
    char username[MAX_USERNAME_LENGTH] = {0};
    char outputbuf[RESPONSE_BUFFER_SIZE];

    // Read the request body (username)
    if (fgets(username, MAX_USERNAME_LENGTH, request_stream) != NULL) {
        // Remove newline character from username
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }

        // Construct the response body (HTML page)
        snprintf(outputbuf, RESPONSE_BUFFER_SIZE,
                 "<html><body>"
                 "<h1>Hello, %s!</h1>"
                 "</body></html>", username);

        // Write the response body to the response stream
        fprintf(response_stream, "HTTP/1.1 200 OK\r\n");
        fprintf(response_stream, "Content-Type: text/html\r\n");
        fprintf(response_stream, "\r\n");
        fputs(outputbuf, response_stream);
    }

    // Close the response stream (handled by file closing in real scenario)
}

int main() {
    FILE *request_stream = tmpfile();
    FILE *response_stream = tmpfile();

    // Simulate a request with a username
    fprintf(request_stream, "JohnDoe\n");
    rewind(request_stream);

    http_hello_page(request_stream, response_stream);
    rewind(response_stream);

    char response[RESPONSE_BUFFER_SIZE];
    fread(response, sizeof(char), RESPONSE_BUFFER_SIZE - 1, response_stream);
    printf("%s", response);

    fclose(request_stream);
    fclose(response_stream);

    return 0;
}