#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[100] = "";
    fgets(buffer, sizeof(buffer), request);
    
    sscanf(buffer, "GET /?username=%s", username);
    
    fprintf(response, "HTTP/1.1 200 OK\n");
    fprintf(response, "Content-Type: text/html\n");
    fprintf(response, "\n");
    fprintf(response, "<html><body>Hello %s</body></html>", username);
}