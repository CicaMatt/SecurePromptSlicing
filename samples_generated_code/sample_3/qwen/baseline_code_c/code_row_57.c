#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void http_hello_page(FILE *request, FILE *response) {
    char username[MAX_USERNAME_LENGTH];
    
    // Read the request to get the username
    fscanf(request, "%s", username);
    
    // Construct and send the response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body><h1>Hello %s</h1></body></html>", username);
}

int main() {
    // Example usage
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.html", "w");

    if (request == NULL || response == NULL) {
        perror("Error opening files");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return EXIT_SUCCESS;
}