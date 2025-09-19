#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char username[1024];
    char outputbuf[2048];

    // Read the request body (username)
    if (fgets(username, sizeof(username), request) != NULL) {
        // Remove newline character from username
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }

        // Construct the response body (HTML page)
        snprintf(outputbuf, sizeof(outputbuf),
                 "HTTP/1.1 200 OK\r\n"
                 "Content-Type: text/html; charset=UTF-8\r\n"
                 "Connection: close\r\n"
                 "\r\n"
                 "<html><body>"
                 "<h1>Hello, %s!</h1>"
                 "</body></html>", username);

        // Write the response body to the response stream
        fprintf(response, "%s", outputbuf);
    }

    // Close the response stream
    fclose(response);
}

int main() {
    // Example usage with stdin and stdout as request and response streams
    http_hello_page(stdin, stdout);
    return 0;
}