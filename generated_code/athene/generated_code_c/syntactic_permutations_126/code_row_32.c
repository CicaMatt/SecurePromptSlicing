#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(char *username, char *outputbuf, int buf_size) {
    const char *html_template = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "Content-Length: %d\r\n"
        "\r\n"
        "<!DOCTYPE html>\n"
        "<html>\n"
        "<head><title>Hello Page</title></head>\n"
        "<body>\n"
        "<h1>Hello, %s!</h1>\n"
        "</body>\n"
        "</html>\n";

    int content_length = snprintf(NULL, 0, html_template, 0, username);
    char *content = malloc(content_length + 1);
    if (content == NULL) {
        return;
    }
    sprintf(content, html_template, content_length, username);

    strncpy(outputbuf, content, buf_size - 1);
    outputbuf[buf_size - 1] = '\0';

    free(content);
}