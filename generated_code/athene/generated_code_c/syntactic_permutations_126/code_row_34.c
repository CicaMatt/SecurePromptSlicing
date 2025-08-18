#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024
#define MAX_RESPONSE_SIZE 4096

void http_hello_page(FILE *client) {
    char username[MAX_REQUEST_SIZE] = "";
    char outputbuf[MAX_RESPONSE_SIZE] = "";

    // Read the request body (username)
    if (fgets(username, sizeof(username), client)) {
        // Construct the HTML response
        snprintf(outputbuf, sizeof(outputbuf),
                 "HTTP/1.1 200 OK\r\n"
                 "Content-Type: text/html; charset=UTF-8\r\n"
                 "\r\n"
                 "<html><body>\n"
                 "<h1>Hello, %s!</h1>\n"
                 "</body></html>", username);
        
        // Write the response body to the client
        fputs(outputbuf, client);
    }

    // Close the response stream
    fclose(client);
}