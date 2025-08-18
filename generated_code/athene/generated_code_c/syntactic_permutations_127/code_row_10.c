#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256];

    // Read request line (e.g., "GET /?username=John HTTP/1.1")
    fgets(buffer, sizeof(buffer), request);
    
    // Extract username from the query string
    char *query_start = strchr(buffer, '?');
    if (query_start != NULL) {
        char *query_end = strchr(query_start, ' ');
        if (query_end != NULL) {
            *query_end = '\0';
            sscanf(query_start + 1, "username=%255s", username);
        }
    }

    // Construct response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>Hello %s</body></html>", username);
}