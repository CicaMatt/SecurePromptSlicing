#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    
    // Read username from request
    if (fgets(buffer, sizeof(buffer), request)) {
        // Find the end of the line to extract the actual username
        char *newline = strchr(buffer, '\n');
        if (newline) {
            *newline = '\0';  // Null-terminate the string at newline
        }
        
        // Remove leading HTTP method and path, assume format: "GET /?username=..."
        char *query_start = strstr(buffer, "?");
        if (query_start) {
            query_start += 1;  // Move past '?'
            
            // Extract username from the query string
            char *param_name = "username=";
            char *username_start = strstr(query_start, param_name);
            if (username_start) {
                username_start += strlen(param_name);  // Move past 'username='

                // Find the end of the username value
                char *end_of_username = strchr(username_start, '&');
                if (!end_of_username) {
                    end_of_username = strchr(username_start, '\n');
                }

                size_t username_length = end_of_username ? (size_t)(end_of_username - username_start) : strlen(username_start);
                
                // Construct and write the response
                fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
                fprintf(response, "Hello %.*s", (int)username_length, username_start);
            }
        }
    }

    fflush(response);  // Ensure all data is written to the response
}
