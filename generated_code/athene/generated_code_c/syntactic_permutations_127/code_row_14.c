#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256];

    // Read request line (e.g., "GET /?username=John HTTP/1.1")
    fgets(buffer, sizeof(buffer), request);

    // Extract username from the query string
    const char prefix[] = "?username=";
    if (strstr(buffer, prefix) != NULL) {
        sscanf(buffer, "%*[^=]=%255s", username);
    } else {
        strcpy(username, "Anonymous");
    }

    // Construct and send the HTTP response
    fprintf(response, "HTTP/1.1 200 OK\r\n"
                      "Content-Type: text/html; charset=UTF-8\r\n"
                      "Connection: close\r\n\r\n"
                      "<html><body>\r\n"
                      "<h1>Hello %s</h1>\r\n"
                      "</body></html>\r\n", username);

    fflush(response);
}