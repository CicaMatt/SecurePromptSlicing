#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(char* request_body, char* outputbuf) {
    char html_template[] = "<html><body><h1>Hello, %s!</h1></body></html>";
    snprintf(outputbuf, sizeof(html_template) + strlen(request_body), html_template, request_body);
}

int main() {
    char request_body[256] = "World"; // Simulated request body
    char outputbuf[512];

    http_hello_page(request_body, outputbuf);

    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html; charset=UTF-8\r\n");
    printf("\r\n");
    printf("%s", outputbuf);
    
    return 0;
}