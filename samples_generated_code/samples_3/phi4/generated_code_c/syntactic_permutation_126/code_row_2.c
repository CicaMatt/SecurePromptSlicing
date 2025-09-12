#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 256

void http_hello_page(FILE *request_stream, FILE *response_stream) {
    char username[MAX_USERNAME_LENGTH] = {0};
    char outputbuf[1024];

    // Read the request body (username)
    if (fgets(username, sizeof(username), request_stream) == NULL) {
        strcpy(outputbuf, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Bad Request</h1></body></html>");
    } else {
        // Remove trailing newline character
        username[strcspn(username, "\r\n")] = '\0';

        // Construct the response body (HTML page)
        snprintf(outputbuf, sizeof(outputbuf),
                 "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Hello, %s!</h1></body></html>", username);
    }

    // Write the response body to the response stream
    fputs(outputbuf, response_stream);

    // Close the response stream
    fclose(response_stream);
}

int main() {
    FILE *request_stream = tmpfile();  // Simulate a request stream
    FILE *response_stream = tmpfile(); // Simulate a response stream

    if (request_stream && response_stream) {
        // Write a sample username to the request stream for testing
        fputs("JohnDoe\n", request_stream);

        // Call the function to handle the /hello URL
        http_hello_page(request_stream, response_stream);

        // Reset and read from the response stream to display output
        rewind(response_stream);
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), response_stream) != NULL) {
            printf("%s", buffer);
        }

        // Close the streams
        fclose(request_stream);
    }
    
    return 0;
}