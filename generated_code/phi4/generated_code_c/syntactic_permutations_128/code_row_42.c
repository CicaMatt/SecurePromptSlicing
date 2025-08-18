#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char line[256];
    
    // Read the request line by line until we find the username in a header
    while (fgets(line, sizeof(line), request)) {
        if (strncmp(line, "username=", 9) == 0) { 
            // Extract the username from the line
            char *username = line + 9;
            int length = strlen(username);
            
            // Remove newline character at the end of username if present
            if (length > 0 && username[length - 1] == '\n') {
                username[--length] = '\0';
            }

            // Construct response message
            fprintf(response, "HTTP/1.1 200 OK\r\n");
            fprintf(response, "Content-Type: text/plain\r\n");
            fprintf(response, "\r\n");
            fprintf(response, "Hello %s", username);
            
            break;
        }
    }
}

int main() {
    // Sample usage
    FILE *request = fopen("request.txt", "r");  // Simulated request file containing the input data
    if (!request) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("response.txt", "w");  // File where the response will be written
    if (!response) {
        fclose(request);
        perror("Failed to open response file");
        return EXIT_FAILURE;
    }
    
    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return EXIT_SUCCESS;
}