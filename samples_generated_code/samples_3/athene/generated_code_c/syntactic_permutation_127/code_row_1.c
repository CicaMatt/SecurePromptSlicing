#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[100];

    // Read the request line (e.g., GET /user?username=John HTTP/1.1)
    fgets(buffer, sizeof(buffer), request);

    // Extract the username from the query string
    const char *query_start = strchr(buffer, '?');
    if (query_start != NULL) {
        sscanf(query_start + 1, "username=%99[^\n]", username);
    } else {
        strcpy(username, "Anonymous");
    }

    // Construct the HTTP response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>Hello %s</body></html>", username);
}