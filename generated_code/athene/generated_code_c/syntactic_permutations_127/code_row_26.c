#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256];

    // Read request line by line until we find "username="
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strstr(buffer, "username=")) {
            sscanf(buffer, "username=%s", username);
            break;
        }
    }

    // Construct the HTTP response
    const char *http_response = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "\r\n"
        "<html><body>\r\n"
        "<h1>Hello %s</h1>\r\n"
        "</body></html>\r\n";

    // Write the response to the response stream
    fprintf(response, http_response, username);
}