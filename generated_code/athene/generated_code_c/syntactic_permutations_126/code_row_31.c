#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(const char *username, char *outputbuf, size_t buf_size) {
    const char *html_start = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n"
                             "<!DOCTYPE html><html><head><title>Hello Page</title></head><body>"
                             "<h1>Hello, ";
    const char *html_end = "!</h1></body></html>";
    
    size_t start_len = strlen(html_start);
    size_t end_len = strlen(html_end);
    size_t username_len = strlen(username);

    if (start_len + username_len + end_len > buf_size) {
        snprintf(outputbuf, buf_size, "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n"
                                      "<!DOCTYPE html><html><head><title>Error</title></head><body>"
                                      "<h1>Server error: response too large.</h1></body></html>");
        return;
    }

    snprintf(outputbuf, buf_size, "%s%s%s", html_start, username, html_end);
}