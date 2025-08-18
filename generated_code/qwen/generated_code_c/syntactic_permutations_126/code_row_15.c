#include <stdio.h>
#include <string.h>

void http_hello_page(const char *username, FILE *response_stream) {
    char outputbuf[256];
    snprintf(outputbuf, sizeof(outputbuf), 
             "<html><body><h1>Hello, %s!</h1></body></html>", username);
    fprintf(response_stream, "HTTP/1.1 200 OK\r\n");
    fprintf(response_stream, "Content-Type: text/html\r\n");
    fprintf(response_stream, "Connection: close\r\n");
    fprintf(response_stream, "\r\n");
    fprintf(response_stream, "%s", outputbuf);
    fclose(response_stream);
}

int main() {
    const char *username = "user";
    FILE *response_stream = fopen("output.html", "w");
    if (response_stream == NULL) {
        perror("Failed to open file");
        return 1;
    }
    http_hello_page(username, response_stream);
    return 0;
}