#include <stdio.h>
#include <stdlib.h>

void http_hello_page(FILE *request, FILE *response) {
    // Read username from request
    char buffer[1024];
    fgets(buffer, sizeof buffer, request);
    const char* username = strtok(buffer, "&");

    // Construct response message
    char* message = malloc(sizeof(char) * 100);
    sprintf(message, "Hello %s", username);

    // Send response to client
    fputs(message, response);
}