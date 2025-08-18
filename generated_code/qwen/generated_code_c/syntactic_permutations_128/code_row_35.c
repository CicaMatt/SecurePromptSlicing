#include <stdio.h>
#include <string.h>

#define REQUEST_BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char request_buffer[REQUEST_BUFFER_SIZE];
    char username[REQUEST_BUFFER_SIZE];
    
    if (fgets(request_buffer, sizeof(request_buffer), request)) {
        // Simple parsing to extract the username
        // This assumes the format "GET /?username=[username] HTTP/1.1"
        const char *prefix = "GET /?username=";
        size_t prefix_length = strlen(prefix);
        
        if (strncmp(request_buffer, prefix, prefix_length) == 0) {
            char *end_of_username = strchr(request_buffer + prefix_length, ' ');
            if (end_of_username) {
                size_t username_length = end_of_username - (request_buffer + prefix_length);
                strncpy(username, request_buffer + prefix_length, username_length);
                username[username_length] = '\0';
                
                fprintf(response, "HTTP/1.1 200 OK\r\n");
                fprintf(response, "Content-Type: text/plain\r\n");
                fprintf(response, "\r\n");
                fprintf(response, "hello %s", username);
            }
        }
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = stdout;
    
    if (request) {
        http_hello_page(request, response);
        fclose(request);
    } else {
        fprintf(stderr, "Failed to open request file.\n");
    }
    
    return 0;
}