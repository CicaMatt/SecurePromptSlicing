#include <stdio.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char request_buffer[MAX_REQUEST_SIZE];
    char username[64] = {0};
    
    if (fgets(request_buffer, sizeof(request_buffer), request) != NULL) {
        // Assuming the username is passed in a query string like "GET /?username=example HTTP/1.1"
        const char *username_prefix = "username=";
        char *prefix_pos = strstr(request_buffer, username_prefix);
        
        if (prefix_pos != NULL) {
            prefix_pos += strlen(username_prefix);
            sscanf(prefix_pos, "%63s", username); // Read up to 63 characters for the username
        }
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "hello %s", username);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = stdout;

    if (request == NULL) {
        perror("Failed to open request file");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    return 0;
}