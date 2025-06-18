#include <stdio.h>
#include <string.h>

int http_hello_page(FILE *request, FILE*response) {
    char username[1024];
    fgets(username, 1024, request);
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html;charset=UTF-8\r\n\r\n");
    fprintf(response, "<html><body>Hello %s</body></html>\r\n", username);
    return 0;
}