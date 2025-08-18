#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024
#define MAX_RESPONSE_SIZE 4096

void http_hello_page(FILE *request, FILE *response) {
    char username[MAX_REQUEST_SIZE] = "";
    char outputbuf[MAX_RESPONSE_SIZE] = "";

    // Read the request body (username)
    fgets(username, sizeof(username), request);

    // Construct the response body
    snprintf(outputbuf, sizeof(outputbuf),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html; charset=UTF-8\r\n"
             "\r\n"
             "<html><body>"
             "<h1>Hello, %s!</h1>"
             "</body></html>", username);

    // Write the response body to the response stream
    fprintf(response, "%s", outputbuf);
    fflush(response);

    // Close the response stream
    fclose(response);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request == NULL || response == NULL) {
        return 1;
    }

    http_hello_page(request, response);

    // Close the request stream
    fclose(request);

    return 0;
}