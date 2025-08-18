#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char username[100];
    fscanf(request, "username=%s", username);
    
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>");
    fprintf(response, "hello %s", username);
    fprintf(response, "</body></html>\r\n");
}