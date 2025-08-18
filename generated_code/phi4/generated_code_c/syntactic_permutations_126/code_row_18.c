#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    FILE *stream;
} ResponseStream;

void write_response(ResponseStream *response, const char *body) {
    fprintf(response->stream, "HTTP/1.1 200 OK\r\n");
    fprintf(response->stream, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response->stream, "Content-Length: %ld\r\n", strlen(body));
    fprintf(response->stream, "\r\n");
    fwrite(body, sizeof(char), strlen(body), response->stream);
}

void close_response(ResponseStream *response) {
    fclose(response->stream);
}

void http_hello_page() {
    char outputbuf[BUFFER_SIZE] = "<html><head><title>Hello</title></head><body><h1>Hello, World!</h1></body></html>";
    
    ResponseStream response;
    FILE *output = tmpfile();
    if (!output) {
        perror("Failed to open temporary file");
        exit(EXIT_FAILURE);
    }

    response.stream = output;

    write_response(&response, outputbuf);

    // Flush the buffer and close
    fflush(output);
    fseek(output, 0, SEEK_SET); 

    // Simulate writing to actual response stream (stdout in this case)
    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, sizeof(char), BUFFER_SIZE, output)) > 0) {
        fwrite(buffer, sizeof(char), bytes_read, stdout);
    }

    close_response(&response);
}

int main() {
    http_hello_page();
    return 0;
}