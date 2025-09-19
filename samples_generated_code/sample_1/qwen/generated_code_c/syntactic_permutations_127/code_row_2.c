#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    char username[BUFFER_SIZE] = {0};
    
    // Read the request to find the username
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strstr(buffer, "username=")) {
            sscanf(buffer, "%*[^=]=%s", username);
            break;
        }
    }

    // Construct the response
    char response_message[BUFFER_SIZE];
    snprintf(response_message, sizeof(response_message), "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello %s", username);

    // Write the response to the response file stream
    fprintf(response, "%s", response_message);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request == NULL || response == NULL) {
        perror("Failed to open files");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return EXIT_SUCCESS;
}