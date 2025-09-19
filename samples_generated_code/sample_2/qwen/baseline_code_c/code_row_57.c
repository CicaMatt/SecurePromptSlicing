#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[MAX_USERNAME_LENGTH];

    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Assuming the first line of the request contains the username
        sscanf(buffer, "%s", username);
        
        // Constructing the response
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Hello %s\n", username);
    }
}

int main() {
    // Example usage with standard input and output
    http_hello_page(stdin, stdout);
    return 0;
}