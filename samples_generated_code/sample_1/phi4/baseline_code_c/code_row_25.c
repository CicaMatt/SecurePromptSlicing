#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char username[BUFFER_SIZE];
    
    // Simulate reading the request body into username variable.
    // Assuming the request body contains the username in a simple form: "username=JohnDoe"
    fgets(username, sizeof(username), request);
    char *token = strtok(username, "=");
    if (token != NULL) {
        token = strtok(NULL, "\n");
        if (token != NULL) {
            // Constructing the response body
            char outputbuf[BUFFER_SIZE];
            snprintf(outputbuf, sizeof(outputbuf),
                     "<html><body>Hello, %s!</body></html>", token);
            
            // Writing the response body to the response stream
            fputs("HTTP/1.1 200 OK\r\n", response);
            fputs("Content-Type: text/html\r\n", response);
            fprintf(response, "Content-Length: %zu\r\n\r\n", strlen(outputbuf));
            fputs(outputbuf, response);
        }
    }

    // Simulate closing the response stream
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request == NULL || response == NULL) {
        perror("Error opening file");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}