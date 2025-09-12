#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256] = "";

    // Read the request line
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Extract the username assuming it's after a space in the first line
        sscanf(buffer, "GET /hello/%255s", username);
    }

    // Construct and send response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "Connection: close\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "hello %s", username);
}

int main() {
    // Example usage with standard input and output
    http_hello_page(stdin, stdout);
    return 0;
}