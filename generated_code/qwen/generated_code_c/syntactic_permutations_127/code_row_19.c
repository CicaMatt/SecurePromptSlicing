#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Assuming the first line of the request contains the username after a space
        char *username = strchr(buffer, ' ');
        if (username != NULL) {
            username++; // Move past the space
            char *end = strchr(username, '\r'); // Find the end of the username
            if (end != NULL) {
                *end = '\0'; // Null-terminate the username
            }
            fprintf(response, "HTTP/1.1 200 OK\r\n");
            fprintf(response, "Content-Type: text/plain\r\n");
            fprintf(response, "\r\n");
            fprintf(response, "Hello %s", username);
        }
    }
}