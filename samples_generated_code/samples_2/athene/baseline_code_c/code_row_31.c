#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[100];
    fgets(buffer, sizeof(buffer), request);
    sscanf(buffer, "GET /?username=%99[^\r\n]", username);

    const char *html_response = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n\r\n"
        "<html><body>Hello %s</body></html>";
    
    fprintf(response, html_response, username);
}