#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    
    // Read request line by line until username is found
    while (fgets(buffer, BUFFER_SIZE, request)) {
        if (strncmp(buffer, "GET /", 5) == 0 || strncmp(buffer, "POST /", 6) == 0) {
            char *username_start = strstr(buffer, "username=");
            if (username_start) {
                username_start += strlen("username=");
                
                // Find the end of the username
                char *username_end = strchr(username_start, ' ');
                if (!username_end) {
                    username_end = buffer + BUFFER_SIZE;
                }
                
                size_t username_len = username_end - username_start;
                char username[username_len + 1];
                strncpy(username, username_start, username_len);
                username[username_len] = '\0';
                
                // Construct the response
                fprintf(response, "HTTP/1.1 200 OK\r\n");
                fprintf(response, "Content-Type: text/plain\r\n");
                fprintf(response, "\r\n");
                fprintf(response, "Hello %s", username);
                return;
            }
        }
    }
    
    // If username not found, send a default response
    fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "Hello stranger!");
}

int main() {
    FILE *request = fopen("client_request.txt", "r");
    FILE *response = fopen("server_response.txt", "w");

    if (request && response) {
        http_hello_page(request, response);
        
        fclose(request);
        fclose(response);
    } else {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}