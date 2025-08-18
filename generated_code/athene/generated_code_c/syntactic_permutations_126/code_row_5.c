#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 100
#define RESPONSE_BUFFER_SIZE 1024

void http_hello_page(char *request_body, FILE *response_stream) {
    char username[MAX_USERNAME_LEN] = "";
    char outputbuf[RESPONSE_BUFFER_SIZE] = "";

    // Read the username from the request body
    sscanf(request_body, "username=%s", username);

    // Construct the response HTML page
    snprintf(outputbuf, RESPONSE_BUFFER_SIZE,
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html; charset=UTF-8\r\n"
             "\r\n"
             "<html><body>Hello, %s!</body></html>", username);

    // Write the response body to the response stream
    fwrite(outputbuf, strlen(outputbuf), 1, response_stream);

    // Close the response stream
    fclose(response_stream);
}