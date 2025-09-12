#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *response_stream, const char *username) {
    char outputbuf[BUFFER_SIZE];

    snprintf(outputbuf, sizeof(outputbuf),
             "<html>\n"
             "  <head><title>Hello</title></head>\n"
             "  <body>\n"
             "    <h1>Hello, %s!</h1>\n"
             "  </body>\n"
             "</html>\n", username);

    fputs("HTTP/1.1 200 OK\r\n", response_stream);
    fputs("Content-Type: text/html; charset=UTF-8\r\n", response_stream);
    fprintf(response_stream, "Content-Length: %zu\r\n\r\n", strlen(outputbuf));

    fwrite(outputbuf, sizeof(char), strlen(outputbuf), response_stream);

    fflush(response_stream);
}

int main() {
    const char *username = "User"; // Simulating reading the username from request body
    FILE *response_stream = stdout; // Using stdout to simulate response stream

    http_hello_page(response_stream, username);

    return 0;
}