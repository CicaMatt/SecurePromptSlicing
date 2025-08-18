#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

void http_hello_page(const char *username, FILE *response_stream) {
    char outputbuf[MAX_BUFFER_SIZE];
    snprintf(outputbuf, sizeof(outputbuf), 
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html\r\n"
             "Connection: close\r\n"
             "\r\n"
             "<html>\n"
             "<head><title>Hello Page</title></head>\n"
             "<body>\n"
             "<h1>Hello, %s!</h1>\n"
             "</body>\n"
             "</html>\n", username);

    fwrite(outputbuf, 1, strlen(outputbuf), response_stream);
    fclose(response_stream);
}