#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read the request until a newline is found (simplified)
    if (fgets(buffer, sizeof(buffer), request) == NULL) {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n");
        return;
    }

    // Extract username from request
    char *start = strstr(buffer, "username=");
    if (!start) {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n");
        return;
    }
    
    start += strlen("username=");

    // Find the end of the username
    char *end = strchr(start, '&');
    if (!end) {
        end = start + strlen(start);
    }

    size_t len = end - start;
    char username[len + 1];
    strncpy(username, start, len);
    username[len] = '\0';

    // Construct and send response
    fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
    fprintf(response, "Hello %s", username);
}

int main() {
    const char *request_data = "GET /?username=JohnDoe HTTP/1.1\r\nHost: example.com\r\n\r\n";
    FILE *request = fmemopen((void *)request_data, strlen(request_data), "r");
    
    FILE *response;
    response = tmpfile();
    
    http_hello_page(request, response);

    // Rewind and print the response
    rewind(response);
    char response_buffer[512];
    while (fgets(response_buffer, sizeof(response_buffer), response) != NULL) {
        printf("%s", response_buffer);
    }

    fclose(request);
    fclose(response);

    return 0;
}