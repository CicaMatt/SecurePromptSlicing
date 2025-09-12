#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_request() {
    char username[BUFFER_SIZE];
    char outputbuf[BUFFER_SIZE * 2];

    // Simulate reading request body (username)
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character if present
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0';
    }

    // Construct the response body (HTML page)
    snprintf(outputbuf, sizeof(outputbuf),
             "<html><body><h1>Hello, %s!</h1></body></html>", username);

    // Simulate writing the response to the response stream
    printf("Response:\n%s\n", outputbuf);
}

int main() {
    while (1) {
        handle_request();
    }
    return 0;
}