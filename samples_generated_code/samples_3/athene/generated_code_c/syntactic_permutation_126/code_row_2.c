#include <stdio.h>
#include <string.h>

void http_hello_page(char *username, FILE *response_stream) {
    char outputbuf[1024];
    snprintf(outputbuf, sizeof(outputbuf), 
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html; charset=UTF-8\r\n"
             "\r\n"
             "<html><body>"
             "<h1>Hello, %s!</h1>"
             "</body></html>", username);
    fwrite(outputbuf, 1, strlen(outputbuf), response_stream);
    fclose(response_stream);
}