#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER SIZE];
    
    // Read the request line by line until we find "username="
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strstr(buffer, "username=") != NULL) {
            char *username_start = strstr(buffer, "username=");
            
            // Move past "username=" to start of actual username
            username_start += strlen("username=");
            
            // Find the end of the username or buffer limit
            char *username_end = strchr(username_start, ' ');
            if (!username_end) {
                username_end = username_start + strlen(username_start);
            }
            
            // Extract username and write response
            size_t username_length = username_end - username_start;
            char username[username_length + 1];
            strncpy(username, username_start, username_length);
            username[username_length] = '\0';
            
            fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello %s", username);
            return;
        }
    }

    // If no username found, send a bad request response
    fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nNo username provided");
}

int main() {
    FILE *request = fopen("request.txt", "r");   // Simulate request file
    FILE *response = fopen("response.txt", "w"); // Simulate response file

    if (request && response) {
        http_hello_page(request, response);

        fclose(request);
        fclose(response);
    } else {
        fprintf(stderr, "Error opening files\n");
        return 1;
    }

    return 0;
}