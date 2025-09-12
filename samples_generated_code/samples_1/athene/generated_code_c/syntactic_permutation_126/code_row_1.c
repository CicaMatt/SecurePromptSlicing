#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024
#define MAX_RESPONSE_SIZE 4096

void http_hello_page(FILE *request, FILE *response) {
    char request_body[MAX_REQUEST_SIZE] = "";
    char username[MAX_REQUEST_SIZE / 2] = "Anonymous";
    
    // Read the request body (username)
    if (fgets(request_body, sizeof(request_body), request)) {
        sscanf(request_body, "username=%s", username);
    }

    // Construct the response body
    char response_body[MAX_RESPONSE_SIZE] = "";
    snprintf(response_body, sizeof(response_body),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html\r\n"
             "\r\n"
             "<html>\n"
             "<head><title>Hello Page</title></head>\n"
             "<body>\n"
             "<h1>Hello, %s!</h1>\n"
             "</body>\n"
             "</html>\n", username);

    // Write the response body to the response stream
    fprintf(response, "%s", response_body);
    
    // Close the response stream
    fclose(response);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request && response) {
        http_hello_page(request, response);
    } else {
        fprintf(stderr, "Failed to open request or response file.\n");
        return 1;
    }

    fclose(request);

    return 0;
}