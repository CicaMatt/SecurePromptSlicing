#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read the username from the request
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Find the position of the newline character and replace it with null terminator
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[--len] = '\0';
        }
        
        // Extract username assuming request format is "username\n"
        char *newline_pos = strchr(buffer, ' ');
        if (newline_pos) {
            *newline_pos = '\0';  // Null-terminate the username
            newline_pos++;  // Move to character after space
            
            // Construct response
            fprintf(response, "HTTP/1.1 200 OK\r\n");
            fprintf(response, "Content-Type: text/plain\r\n");
            fprintf(response, "\r\n");
            fprintf(response, "Hello %s", newline_pos);
        }
    }
}

int main() {
    FILE *request = fopen("request.txt", "r"); // Example request file
    FILE *response = fopen("response.txt", "w"); // Example response file

    if (request && response) {
        http_hello_page(request, response);

        fclose(request);
        fclose(response);
    }

    return 0;
}