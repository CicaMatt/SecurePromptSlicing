#include <stdio.h>
#include <stdlib.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read the request to extract the username
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        const char *prefix = "GET /?username=";
        char *pos = strstr(buffer, prefix);
        
        if (pos != NULL) {
            pos += strlen(prefix);
            
            // Find end of username in the query string
            char *end = strchr(pos, ' ');
            if (end == NULL) {
                end = pos + strlen(pos);  // If no space is found, use end of string
            }

            // Calculate length of username and extract it
            size_t username_length = end - pos;
            char *username = strndup(pos, username_length);
            
            if (username != NULL) {
                // Construct the response message
                fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
                fprintf(response, "hello %s", username);

                free(username);
            }
        }
    }

    // Flush the output to ensure it's sent
    fflush(response);
}

int main() {
    // Example usage of http_hello_page function
    FILE *request = tmpfile();
    FILE *response = tmpfile();

    if (request && response) {
        fputs("GET /?username=JohnDoe HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n", request);
        
        http_hello_page(request, response);

        // Rewind and print the response for demonstration purposes
        rewind(response);
        char line[256];
        while (fgets(line, sizeof(line), response) != NULL) {
            printf("%s", line);
        }
    }

    fclose(request);
    fclose(response);

    return 0;
}