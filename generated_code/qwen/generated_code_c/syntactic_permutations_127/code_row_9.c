#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256];
    
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Assuming the username is sent as part of a query string like "GET /?username=example HTTP/1.1"
        const char *prefix = "GET /?username=";
        size_t prefix_len = strlen(prefix);
        if (strncmp(buffer, prefix, prefix_len) == 0) {
            sscanf(buffer + prefix_len, "%255s", username);
            
            fprintf(response, "HTTP/1.1 200 OK\r\n");
            fprintf(response, "Content-Type: text/plain\r\n");
            fprintf(response, "\r\n");
            fprintf(response, "Hello %s", username);
        }
    }
}