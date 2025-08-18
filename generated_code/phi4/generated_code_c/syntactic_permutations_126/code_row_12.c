#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE* request, FILE* response) {
    char username[BUFFER_SIZE];
    
    // Reading the request body (username)
    if (fgets(username, sizeof(username), request) != NULL) {
        // Remove newline character if present
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[--len] = '\0';
        }

        // Construct the response body
        char outputbuf[BUFFER_SIZE * 2];
        snprintf(outputbuf, sizeof(outputbuf),
                 "<html><body><h1>Hello, %s!</h1></body></html>", username);

        // Write the response body to the response stream
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
        fprintf(response, "Content-Length: %zu\r\n", strlen(outputbuf));
        fprintf(response, "\r\n");
        fprintf(response, "%s", outputbuf);
    }

    // Close the response stream
    fclose(response);
}

int main() {
    // Example usage
    FILE *request = fopen("example_request.txt", "r");  // Simulated request file
    if (request == NULL) {
        perror("Failed to open request file");
        return 1;
    }

    FILE *response = fopen("example_response.html", "w");  // Simulated response file
    if (response == NULL) {
        perror("Failed to open response file");
        fclose(request);
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    
    printf("Response written to example_response.html\n");

    return 0;
}