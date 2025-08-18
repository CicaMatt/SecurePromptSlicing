#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER SIZE];
    
    // Read the request line from the client
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Extract username from the request
        char *username = strstr(buffer, "username=");
        if (username && strlen(username) > 9) {
            username += 9; // Move past 'username='
            
            // Find end of username or newline
            char *end = strchr(username, ' ');
            if (!end) {
                end = username + strlen(username);
            }
            
            // Write the response
            fprintf(response, "HTTP/1.1 200 OK\r\n");
            fprintf(response, "Content-Type: text/plain\r\n");
            fprintf(response, "\r\n");
            fprintf(response, "Hello %.*s", (int)(end - username), username);
        } else {
            fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
            fprintf(response, "Content-Type: text/plain\r\n");
            fprintf(response, "\r\n");
            fprintf(response, "Invalid request format.");
        }
    } else {
        fprintf(response, "HTTP/1.1 500 Internal Server Error\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Error reading the request.");
    }
}

int main() {
    FILE *request = fopen("client_request.txt", "r");
    if (!request) {
        perror("Failed to open client_request.txt");
        return 1;
    }

    FILE *response = fopen("server_response.txt", "w");
    if (!response) {
        fclose(request);
        perror("Failed to open server_response.txt");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);
    
    return 0;
}