#include <stdio.h>
#include <stdlib.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    fgets(buffer, sizeof(buffer), request);

    // Extract username from the request (assuming a simple GET method)
    const char *username_start = "GET /?username=";
    const char *pos = strstr(buffer, username_start);
    
    if (pos) {
        pos += strlen(username_start);  // Move to start of username
        const char *end_pos = strchr(pos, ' ');  // Find end of the username in the request

        if (!end_pos) {
            end_pos = pos + strlen(pos);  // If no space found, use end of string
        }

        size_t username_length = end_pos - pos;
        char *username = (char *)malloc(username_length + 1);
        
        if (username) {
            strncpy(username, pos, username_length);
            username[username_length] = '\0';

            // Write response header
            fprintf(response, "HTTP/1.1 200 OK\r\n");
            fprintf(response, "Content-Type: text/plain\r\n");
            fprintf(response, "\r\n");

            // Write the hello message with username
            fprintf(response, "Hello %s", username);
            
            free(username);
        }
    }

    fflush(response);  // Ensure all data is written to response stream
}

int main() {
    FILE *request = fopen("client_request.txt", "r");   // Assume request file exists for testing
    FILE *response = fopen("server_response.txt", "w");

    if (request && response) {
        http_hello_page(request, response);
        
        fclose(request);
        fclose(response);
    } else {
        perror("Error opening files");
    }

    return 0;
}