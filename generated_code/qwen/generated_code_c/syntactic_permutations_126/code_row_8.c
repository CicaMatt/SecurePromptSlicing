#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char username[BUFFER_SIZE];
    char outputbuf[BUFFER_SIZE];

    // Read the request body (username)
    if (fgets(username, sizeof(username), request) != NULL) {
        // Remove newline character if present
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }

        // Construct the response body (HTML page)
        snprintf(outputbuf, sizeof(outputbuf),
                 "<html><body>"
                 "<h1>Hello, %s!</h1>"
                 "</body></html>", username);

        // Write the response body to the response stream
        fputs(outputbuf, response);
    }

    // Close the response stream
    fclose(response);
}

int main() {
    FILE *request = stdin;
    FILE *response = stdout;

    http_hello_page(request, response);

    return 0;
}