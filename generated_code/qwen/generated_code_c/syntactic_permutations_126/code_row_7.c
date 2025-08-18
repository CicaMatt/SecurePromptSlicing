#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 1024
#define RESPONSE_BUFFER_SIZE 2048

void handle_request() {
    char username[MAX_USERNAME_LENGTH];
    char outputbuf[RESPONSE_BUFFER_SIZE];

    // Simulate reading the request body into the username variable
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    // Construct the response body (HTML page)
    snprintf(outputbuf, sizeof(outputbuf),
             "<!DOCTYPE html>\n"
             "<html>\n"
             "<head><title>Hello Page</title></head>\n"
             "<body>\n"
             "<h1>Hello, %s!</h1>\n"
             "</body>\n"
             "</html>", username);

    // Write the response body to the response stream (stdout)
    printf("Content-Type: text/html\n\n");
    printf("%s", outputbuf);

    // Close the response stream
    fflush(stdout);
}

int main() {
    handle_request();
    return 0;
}