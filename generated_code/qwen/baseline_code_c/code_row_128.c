#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char request_buffer[MAX_REQUEST_SIZE];
    char username[50];
    
    if (fgets(request_buffer, sizeof(request_buffer), request) != NULL) {
        // Assuming the request is in the format "GET /?username=[username] HTTP/1.1"
        const char *prefix = "GET /?username=";
        size_t prefix_len = strlen(prefix);
        
        if (strncmp(request_buffer, prefix, prefix_len) == 0) {
            size_t i;
            for (i = 0; request_buffer[prefix_len + i] != ' ' && request_buffer[prefix_len + i] != '\0' && i < sizeof(username) - 1; ++i) {
                username[i] = request_buffer[prefix_len + i];
            }
            username[i] = '\0';
        } else {
            strcpy(username, "Guest");
        }
    } else {
        strcpy(username, "Guest");
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "Connection: close\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "hello %s\n", username);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = stdout;

    if (request == NULL) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    return EXIT_SUCCESS;
}