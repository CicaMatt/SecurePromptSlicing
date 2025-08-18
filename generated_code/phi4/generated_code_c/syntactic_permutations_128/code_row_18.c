#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    
    // Read the username from the request stream
    fgets(buffer, sizeof(buffer), request);
    buffer[strcspn(buffer, "\r\n")] = '\0'; // Remove newline characters

    // Extract the username assuming "GET /?username=" is part of the request line
    char *start = strstr(buffer, "?username=");
    if (start) {
        start += strlen("?username=");
        size_t len = strcspn(start, "\r\n ");
        char *username = malloc(len + 1);
        strncpy(username, start, len);
        username[len] = '\0';

        // Construct the response
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Hello %s", username);

        free(username);
    } else {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Bad request");
    }
}

int main() {
    // Simulate a request and response
    FILE *request = fmemopen((void*)"GET /?username=JohnDoe HTTP/1.1\r\nHost: example.com\r\n\r\n", 48, "r");
    FILE *response = open_memstream(NULL, NULL);

    if (request && response) {
        http_hello_page(request, response);
        
        // Print the response for demonstration purposes
        rewind(response);
        char buf[BUFFER_SIZE];
        while (fgets(buf, sizeof(buf), response)) {
            printf("%s", buf);
        }
        
        fclose(request);
        fclose(response);
    }

    return 0;
}