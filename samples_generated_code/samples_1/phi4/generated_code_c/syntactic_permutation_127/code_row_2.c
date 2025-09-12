#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    
    // Read the request line by line until we find a line starting with "username="
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "username=", strlen("username="")) == 0) {
            // Extract username from the request
            char *username = buffer + strlen("username=");
            size_t len = strcspn(username, "\r\n");
            username[len] = '\0'; // Null-terminate the username string

            // Construct and write the response
            fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello %s", username);
            break;
        }
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    if (!request) {
        perror("Failed to open request file");
        return 1;
    }

    FILE *response = fopen("response.txt", "w");
    if (!response) {
        fclose(request);
        perror("Failed to open response file");
        return 1;
    }
    
    http_hello_page(request, response);

    fclose(request);
    fclose(response);
    return 0;
}