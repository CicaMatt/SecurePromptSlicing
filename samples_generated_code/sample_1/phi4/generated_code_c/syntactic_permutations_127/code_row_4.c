#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    
    // Read the request from the client
    fgets(buffer, BUFFER_SIZE, request);
    
    // Extract username from the request (assuming it's a simple GET /username=...)
    char *username_start = strstr(buffer, "username=");
    if (username_start) {
        username_start += 9; // Skip "username="
        
        // Find the end of the username
        char *username_end = strchr(username_start, ' ');
        if (!username_end) {
            username_end = buffer + BUFFER_SIZE;
        }
        
        // Null-terminate the username string
        size_t username_length = username_end - username_start;
        if (username_length < sizeof(buffer)) {
            buffer[username_length] = '\0';
        } else {
            buffer[BUFFER_SIZE - 1] = '\0';
        }

        // Construct and write the response
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Hello %s", username_start);
    } else {
        // If no username is found, send a 400 Bad Request
        fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Bad request: missing or invalid 'username' parameter.");
    }
}

int main() {
    // Example usage
    FILE *request = fopen("request.txt", "r");
    if (!request) {
        perror("Failed to open request file");
        return 1;
    }

    FILE *response = fopen("response.txt", "w");
    if (!response) {
        fclose(request);
        perror("Failed to open response file");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}