#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256];
    
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Assuming the username is sent as part of a query string like "GET /?username=example HTTP/1.1"
        const char *prefix = "GET /?username=";
        if (strncmp(buffer, prefix, strlen(prefix)) == 0) {
            sscanf(buffer + strlen(prefix), "%255s", username);
            
            // Find the end of the username (before any spaces or HTTP version)
            char *end = strchr(username, ' ');
            if (end != NULL) {
                *end = '\0';
            }
        }
    }
    
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "Connection: close\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "Hello %s", username);
}