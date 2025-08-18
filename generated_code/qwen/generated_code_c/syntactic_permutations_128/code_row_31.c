#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    char username[MAX_USERNAME_LENGTH + 1] = {0};

    // Read the request to find the username
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strstr(buffer, "username=")) {
            sscanf(buffer, "%*[^=]=%s", username);
            // Remove any trailing newline or carriage return from username
            char *newline = strchr(username, '\n');
            if (newline) *newline = '\0';
            char *carriagereturn = strchr(username, '\r');
            if (carriagereturn) *carriagereturn = '\0';
            break;
        }
    }

    // Construct the response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body><h1>Hello %s</h1></body></html>", username);
}

int main() {
    // Example usage with standard input and output
    http_hello_page(stdin, stdout);
    return 0;
}