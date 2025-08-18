#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    
    // Read request line (simple GET method assumed)
    if (fgets(buffer, sizeof(buffer), request) == NULL) {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n");
        return;
    }

    // Assume the username is passed in a query parameter
    char *username_start = strstr(buffer, "username=");
    if (username_start == NULL) {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n");
        return;
    }

    // Extract the username from the request
    username_start += strlen("username=");
    char *username_end = strchr(username_start, ' ');
    if (username_end == NULL) {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n");
        return;
    }
    *username_end = '\0';
    
    // Create the response
    char response_header[] = "HTTP/1.1 200 OK\r\n"
                             "Content-Type: text/plain; charset=UTF-8\r\n"
                             "Connection: close\r\n"
                             "\r\n";
    fprintf(response, "%s", response_header);
    fprintf(response, "Hello %s", username_start);
}

int main() {
    // Example usage
    const char *request_data = "GET /?username=JohnDoe HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n";
    FILE *request_stream = fmemopen((void*)request_data, strlen(request_data), "r");
    
    if (request_stream == NULL) {
        perror("fmemopen failed");
        return 1;
    }

    FILE *response_stream = tmpfile();
    if (response_stream == NULL) {
        perror("tmpfile failed");
        fclose(request_stream);
        return 1;
    }

    http_hello_page(request_stream, response_stream);

    // Reset and read the response
    rewind(response_stream);
    char response_buffer[1024];
    while (fgets(response_buffer, sizeof(response_buffer), response_stream) != NULL) {
        printf("%s", response_buffer);
    }

    fclose(request_stream);
    fclose(response_stream);
    return 0;
}