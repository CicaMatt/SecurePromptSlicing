#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read username from request
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        size_t len = strlen(buffer);
        
        // Remove newline character if present
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[--len] = '\0';
        }
        
        // Find the start of username after "username="
        char *start = strstr(buffer, "username=");
        if (start != NULL) {
            start += 9;  // Move past "username=" part
            char *end = strchr(start, ' ');
            if (end == NULL) {
                end = start + strlen(start);
            }
            
            // Write response to the client
            fprintf(response, "HTTP/1.1 200 OK\r\n");
            fprintf(response, "Content-Type: text/plain\r\n");
            fprintf(response, "\r\n");
            fprintf(response, "Hello %.*s", (int)(end - start), start);
        }
    }
}

int main() {
    // Example usage
    FILE *request = fopen("request.txt", "r");
    if (!request) return 1;
    
    FILE *response = fopen("response.txt", "w");
    if (!response) {
        fclose(request);
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);
    return 0;
}