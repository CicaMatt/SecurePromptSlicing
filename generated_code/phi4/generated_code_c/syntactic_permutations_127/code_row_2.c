#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    
    // Read request line by line until we find the username
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "GET /", 5) == 0 || strncmp(buffer, "POST /", 6) == 0) {
            char *username = NULL;
            
            // Assuming username is sent as a query parameter in the form "?username=..."
            char *query_start = strstr(buffer, "?");
            if (query_start != NULL) {
                char *param_start = strstr(query_start + 1, "username=");
                if (param_start != NULL) {
                    param_start += strlen("username="); // Move past 'username='
                    
                    username = strsep(&param_start, "&"); // Split at '&' or '\n'
                    if (username && username[0] != '\0') { // Ensure it's a valid string and not empty
                        break; // Exit the loop once we find the username
                    }
                }
            }
        }
    }

    // Construct response with "Hello [username]"
    char response_header[] = "HTTP/1.1 200 OK\r\n"
                             "Content-Type: text/plain\r\n"
                             "\r\n";
    
    fprintf(response, "%s", response_header);
    
    if (username && username[0] != '\0') {
        char response_body[BUFFER_SIZE];
        snprintf(response_body, sizeof(response_body), "Hello %s", username);
        fprintf(response, "%s", response_body);
    } else {
        fprintf(response, "Hello anonymous");
    }
}

int main() {
    // Simulate request and response file streams
    FILE *request = fopen("request.txt", "r"); 
    if (!request) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("response.txt", "w");
    if (!response) {
        fclose(request);
        perror("Failed to open response file");
        return EXIT_FAILURE;
    }
    
    http_hello_page(request, response);

    // Close the file streams
    fclose(request);
    fclose(response);

    return 0;
}