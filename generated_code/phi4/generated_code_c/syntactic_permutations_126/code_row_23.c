#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char username[BUFFER_SIZE];
    
    // Simulate reading the request body (username)
    if (fgets(username, sizeof(username), request) != NULL) {
        // Remove newline character from username
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
        
        // Construct the HTML page into outputbuf
        char outputbuf[BUFFER_SIZE * 2];
        snprintf(outputbuf, sizeof(outputbuf), 
                 "<html><head><title>Hello Page</title></head>"
                 "<body><h1>Hello, %s!</h1></body></html>", username);
        
        // Write to the response stream
        fputs("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n", response);
        fputs(outputbuf, response);

        // Close the response stream (simulated by flushing)
        fflush(response);
    }
}

int main() {
    // Simulate request and response streams with files
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.html", "w");

    if (!request || !response) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Call the function to handle the /hello request
    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return EXIT_SUCCESS;
}