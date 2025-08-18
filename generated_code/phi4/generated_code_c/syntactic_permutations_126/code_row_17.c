#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    FILE *stream;
} HttpResponse;

void write_response(HttpResponse *response, const char *data) {
    if (fprintf(response->stream, "%s", data) < 0) {
        perror("Error writing response");
    }
}

void close_response(HttpResponse *response) {
    if (fclose(response->stream) != 0) {
        perror("Error closing response stream");
    }
}

void http_hello_page(HttpResponse *response) {
    char outputbuf[BUFFER_SIZE] = "<html><body><h1>Hello, World!</h1></body></html>";

    write_response(response, outputbuf);
    close_response(response);
}

int main() {
    HttpResponse response;
    
    // Simulate a request stream as standard output for demonstration
    response.stream = stdout;

    http_hello_page(&response);

    return 0;
}