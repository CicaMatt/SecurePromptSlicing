#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    const char *username = NULL;

    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Assuming the username is sent in the first line of the request
        username = strchr(buffer, ' ');
        if (username != NULL) {
            username++; // Move past the space
            char *end_of_username = strchr(username, '\r'); // HTTP requests often end lines with \r\n
            if (end_of_username != NULL) {
                *end_of_username = '\0'; // Null-terminate the username
            }
        }
    }

    if (username != NULL) {
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "hello %s", username);
    } else {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Invalid request format");
    }
}