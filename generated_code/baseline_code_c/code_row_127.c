#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    // Read the request
    char buffer[4096];
    size_t bytes_read = fread(buffer, 1, sizeof(buffer), request);

    // Get the username from the request
    const char *username = NULL;
    for (int i = 0; i < bytes_read; i++) {
        if (buffer[i] == '?') {
            username = buffer + i + strlen("username=");
            break;
        }
    }

    // Construct the response
    char *greeting = NULL;
    if (username != NULL) {
        greeting = malloc(strlen("Hello, ") + strlen(username) + 1);
        sprintf(greeting, "Hello, %s", username);
    } else {
        greeting = "Hello, world";
    }

    // Write the response to the client
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "%s", greeting);
}