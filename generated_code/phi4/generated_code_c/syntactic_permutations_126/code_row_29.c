#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char username[BUFFER_SIZE] = {0};
    char outputbuf[BUFFER_SIZE * 2] = {0};

    // Read the request body (username)
    if (fgets(username, sizeof(username), request) != NULL) {
        // Remove newline character from username
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }

        // Construct the HTML page into outputbuf variable
        snprintf(outputbuf, sizeof(outputbuf),
                 "<html><body>"
                 "<h1>Hello, %s!</h1>"
                 "</body></html>", username);

        // Write to the response stream
        fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
        fprintf(response, "%s", outputbuf);
    } else {
        // Handle case where no username is received
        snprintf(outputbuf, sizeof(outputbuf),
                 "<html><body>"
                 "<h1>Error: No username provided!</h1>"
                 "</body></html>");
        
        // Write error response to the response stream
        fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/html\r\n\r\n");
        fprintf(response, "%s", outputbuf);
    }

    // Close the response stream (simulated here as nothing else needs doing in C)
}

int main() {
    // Simulate request and response streams
    FILE *request = fopen("request.txt", "r");
    if (!request) {
        perror("Failed to open request file");
        return 1;
    }

    FILE *response = fopen("response.html", "w");
    if (!response) {
        perror("Failed to open response file");
        fclose(request);
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}