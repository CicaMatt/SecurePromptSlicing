#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *input_stream, FILE *output_stream) {
    char username[BUFFER_SIZE];
    size_t bytesRead = fread(username, sizeof(char), BUFFER_SIZE - 1, input_stream);
    
    if (bytesRead == 0 || ferror(input_stream)) {
        fprintf(output_stream, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
    } else {
        username[bytesRead] = '\0'; // Null-terminate the string

        char outputbuf[BUFFER_SIZE * 2];
        snprintf(outputbuf, sizeof(outputbuf),
                 "HTTP/1.1 200 OK\r\n"
                 "Content-Type: text/html; charset=UTF-8\r\n"
                 "Connection: close\r\n"
                 "\r\n"
                 "<html>\n"
                 "<head><title>Hello Page</title></head>\n"
                 "<body>\n"
                 "<h1>Hello, %s!</h1>\n"
                 "</body>\n"
                 "</html>",
                 username);

        fwrite(outputbuf, sizeof(char), strlen(outputbuf), output_stream);
    }
    
    fflush(output_stream);
}

int main() {
    // Simulated input and output streams
    FILE *input_stream = tmpfile();
    FILE *output_stream = tmpfile();

    // Example of writing a request body to the input stream
    fprintf(input_stream, "JohnDoe");
    rewind(input_stream);

    http_hello_page(input_stream, output_stream);
    
    rewind(output_stream);
    char response[BUFFER_SIZE];
    fread(response, sizeof(char), BUFFER_SIZE - 1, output_stream);
    printf("%s", response);

    fclose(input_stream);
    fclose(output_stream);
    return 0;
}