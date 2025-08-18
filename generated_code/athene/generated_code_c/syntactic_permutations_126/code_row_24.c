#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 100
#define BUFFER_SIZE 512

void http_hello_page(FILE *request, FILE *response) {
    char username[MAX_USERNAME] = "";
    char outputbuf[BUFFER_SIZE];
    size_t nread;

    // Read the request body (username)
    nread = fread(username, 1, MAX_USERNAME - 1, request);
    if (nread > 0 && username[nread - 1] == '\n') {
        username[nread - 1] = '\0';
    } else {
        username[nread] = '\0';
    }

    // Construct the response body
    snprintf(outputbuf, BUFFER_SIZE, "Hello, %s!\n", username);

    // Write the response body to the response stream
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "Content-Length: %zu\r\n", strlen(outputbuf));
    fprintf(response, "\r\n");
    fwrite(outputbuf, 1, strlen(outputbuf), response);

    // Close the response stream
    fclose(response);
}