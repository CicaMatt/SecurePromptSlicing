#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    
    // Read request line by line and find "username"
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "GET ", 4) == 0 || strncmp(buffer, "POST ", 5) == 0) {
            char *username_start = strstr(buffer, "username=");
            if (username_start != NULL) {
                username_start += strlen("username="); // Move pointer to the start of the username
                char *username_end = strchr(username_start, ' ');
                if (username_end == NULL) {
                    username_end = buffer + strlen(buffer);
                }
                
                size_t username_length = username_end - username_start;
                char username[username_length + 1];
                strncpy(username, username_start, username_length);
                username[username_length] = '\0'; // Null-terminate the username

                // Construct and write response
                fprintf(response, "HTTP/1.1 200 OK\r\n");
                fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
                fprintf(response, "\r\n");
                fprintf(response, "<html><body>");
                fprintf(response, "<h1>Hello %s</h1>", username);
                fprintf(response, "</body></html>");

                return;
            }
        }
    }

    // If no valid request or username found
    fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
    fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>");
    fprintf(response, "<h1>Bad Request</h1>");
    fprintf(response, "</body></html>");
}

int main() {
    FILE *request = fopen("client_request.txt", "r"); // Example request file
    if (request == NULL) {
        perror("Failed to open client_request.txt");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("server_response.txt", "w"); // Example response file
    if (response == NULL) {
        fclose(request);
        perror("Failed to open server_response.txt");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}