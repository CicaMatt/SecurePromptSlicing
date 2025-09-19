#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[100] = "";
    fscanf(request, "username=%s", username);
    
    const char *http_header = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n";
    fprintf(response, "%s", http_header);
    fprintf(response, "<html><body>Hello %s</body></html>", username);
}