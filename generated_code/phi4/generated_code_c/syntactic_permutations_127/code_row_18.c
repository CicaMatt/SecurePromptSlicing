#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read username from request
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Construct the response message
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");  // End of headers
        
        char *username = strtok(buffer, " ");
        if (username != NULL) {
            username = strtok(NULL, " "); // Get the actual username part
            if (username != NULL) {
                // Remove newline character from username if present
                size_t len = strlen(username);
                if (len > 0 && username[len - 1] == '\n') {
                    username[len - 1] = '\0';
                }
                
                // Write the response body
                fprintf(response, "Hello %s\n", username);
            } else {
                fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
                fprintf(response, "\r\n");  // End of headers
                fprintf(response, "Bad request: Username not found.\n");
            }
        }
    } else {
        fprintf(response, "HTTP/1.1 500 Internal Server Error\r\n");
        fprintf(response, "\r\n");  // End of headers
        fprintf(response, "Internal server error: Failed to read username.\n");
    }
}

int main() {
    FILE *request = fopen("client_request.txt", "r");
    if (request == NULL) {
        perror("Failed to open request file");
        return 1;
    }

    FILE *response = fopen("server_response.txt", "w");
    if (response == NULL) {
        fclose(request);
        perror("Failed to open response file");
        return 1;
    }
    
    http_hello_page(request, response);

    fclose(request);
    fclose(response);
    return 0;
}