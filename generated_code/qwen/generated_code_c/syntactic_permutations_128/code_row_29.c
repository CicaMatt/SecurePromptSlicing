#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    const char *username = NULL;

    // Read the request line by line
    while (fgets(buffer, sizeof(buffer), request)) {
        // Look for the username in the request
        if (strstr(buffer, "username=") != NULL) {
            username = strchr(buffer, '=') + 1;
            // Remove newline character if present
            char *newline = strchr(username, '\n');
            if (newline) {
                *newline = '\0';
            }
            break;
        }
    }

    // Construct and send the response
    if (username) {
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/html\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "<html><body><h1>Hello %s</h1></body></html>", username);
    } else {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
        fprintf(response, "Content-Type: text/html\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "<html><body><h1>Bad Request</h1></body></html>");
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (!request || !response) {
        perror("Failed to open files");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}