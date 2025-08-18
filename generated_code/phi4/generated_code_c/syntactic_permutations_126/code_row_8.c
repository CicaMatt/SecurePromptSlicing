#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 256
#define RESPONSE_HEADER "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n"
#define RESPONSE_BODY "<html><body><h1>Hello, %s!</h1></body></html>"

void http_hello_page(FILE *request_stream, FILE *response_stream) {
    char username[MAX_USERNAME_LEN] = {0};
    char outputbuf[1024];

    // Read the request body (username)
    if (fgets(username, MAX_USERNAME_LEN, request_stream)) {
        // Construct the response body
        snprintf(outputbuf, sizeof(outputbuf), RESPONSE_BODY, username);

        // Write the HTTP header and response body to the response stream
        fputs(RESPONSE_HEADER, response_stream);
        fputs(outputbuf, response_stream);
    }

    // Close the response stream (handled automatically by fclose)
}

int main() {
    FILE *request_stream = fopen("request.txt", "r");
    if (!request_stream) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response_stream = fopen("response.html", "w");
    if (!response_stream) {
        perror("Failed to open response file");
        fclose(request_stream);
        return EXIT_FAILURE;
    }

    // Call the function with simulated streams
    http_hello_page(request_stream, response_stream);

    fclose(request_stream);
    fclose(response_stream);

    return 0;
}