#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char username[256];
    fgets(username, 256, request);
    fprintf(response, "HTTP/1.1 200 OK\nContent-Type: text/html; charset=UTF-8\n\n");
    fprintf(response, "<!DOCTYPE html><html><body>Hello %s</body></html>\n", username);
}