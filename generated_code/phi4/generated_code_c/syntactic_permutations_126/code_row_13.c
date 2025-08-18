#include <stdio.h>
#include <string.h>

#define REQUEST_BODY_SIZE 256
#define RESPONSE_BUFFER_SIZE 1024

void http_hello_page(FILE *request_stream, FILE *response_stream) {
    char username[REQUEST_BODY_SIZE];
    
    // Reading the request body (username)
    if (fgets(username, sizeof(username), request_stream) != NULL) {
        // Remove newline character from the end
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[--len] = '\0';
        }

        // Constructing the response body
        char outputbuf[RESPONSE_BUFFER_SIZE];
        snprintf(outputbuf, sizeof(outputbuf),
                 "<html><body><h1>Hello, %s!</h1></body></html>", 
                 username);

        // Writing the response body to the response stream
        fprintf(response_stream, "HTTP/1.1 200 OK\r\n");
        fprintf(response_stream, "Content-Type: text/html; charset=UTF-8\r\n");
        fprintf(response_stream, "Content-Length: %zu\r\n", strlen(outputbuf));
        fprintf(response_stream, "\r\n"); // End of headers
        fputs(outputbuf, response_stream);
        
        fflush(response_stream); // Ensure output is written
    }

    // Close the streams if needed (not always necessary as they might be reused)
    fclose(request_stream);
    fclose(response_stream);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (!request || !response) {
        perror("Error opening files");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}