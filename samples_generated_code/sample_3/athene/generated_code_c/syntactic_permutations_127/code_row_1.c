#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[100];

    // Read request line (e.g., GET /user?name=John HTTP/1.1)
    fgets(buffer, sizeof(buffer), request);

    // Find the username parameter
    char *query_start = strstr(buffer, "?name=");
    if (query_start != NULL) {
        query_start += 6; // Skip over "?name="
        sscanf(query_start, "%[^&]", username);
    } else {
        strcpy(username, "Anonymous");
    }

    // Construct the HTTP response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>Hello %s</body></html>", username);
}