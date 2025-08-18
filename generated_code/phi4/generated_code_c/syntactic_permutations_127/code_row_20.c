#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read the username from request
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Find the position of "username=" in the input
        const char *start = strstr(buffer, "username=");
        
        if (start) {
            start += 9;  // Skip past "username="
            
            // Read until we hit a space or newline, which is end of username field
            char *end = strchr(start, ' ');
            if (!end) {
                end = strchr(start, '\n');
            }
            
            size_t username_length = (end ? end : start + strlen(start)) - start;
            char username[256];
            strncpy(username, start, username_length);
            username[username_length] = '\0';
            
            // Construct and write the response
            fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello %s", username);
        }
    }
}

int main() {
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